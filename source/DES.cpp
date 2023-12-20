#include "../include/DES.h"


void DES::des_encrypt_block(char unsigned *to, bool mode, unsigned length, char unsigned *from, unsigned long long *keys48b, unsigned long long iv = 0) {
    length = (length % 8 == 0 ? length : length + (8 - (length % 8)));
    unsigned long long previous_block = iv;

    for (unsigned i = 0; i < length; i += 8) {
        unsigned long long block64b = 0;
        for (int j = 0; j < 8; ++j) {
            block64b = (block64b << 8) | from[i + j];
        }

        // XOR with the previous block in CBC mode
        if (iv != 0) {
            block64b ^= previous_block;
        }

        unsigned long N1, N2;
        split_64bits_to_32bits(initial_permutation(block64b), &N1, &N2);
        feistel_cipher(mode, &N1, &N2, keys48b);
        previous_block = final_permutation(join_32bits_to_64bits(N2, N1));

        split_64bits_to_8bits(previous_block, to + i);
    }
}

inline void DES::split_64bits_to_32bits(unsigned long long block64b, unsigned long *block32b_1, unsigned long *block32b_2) {
    *block32b_1 = static_cast<unsigned long>(block64b >> 32);
    *block32b_2 = static_cast<unsigned long>(block64b);
}

unsigned long long DES::initial_permutation(unsigned long long block64b) {
    unsigned long long new_block64b = 0;
    for (char unsigned i = 0; i < 64; ++i) {
        new_block64b |= ((block64b >> (64 - __IP[i])) & 0x01) << (63 - i);
    }
    return new_block64b;
}

void DES::feistel_cipher(bool mode, unsigned long *N1, unsigned long *N2, unsigned long long *keys48b) {
    switch (mode) {
        case true: {
            for (signed round = 0; round < 16; ++round) {
                round_feistel_cipher(N1, N2, keys48b[round]);
            }
            std::swap(N1, N2);
            break;
        }
        case false: {
            for (signed round = 15; round >= 0; --round) {
                round_feistel_cipher(N1, N2, keys48b[round]);
            }
            std::swap(N1, N2);
            break;
        }
    }
}

void DES::round_feistel_cipher(unsigned long *N1, unsigned long *N2, unsigned long long key48b) {
    unsigned long temp = *N2;
    *N2 = func_F(*N2, key48b) ^ *N1;
    *N1 = temp;
}

unsigned long DES::func_F(unsigned long block32b, unsigned long long key48b) {
    unsigned long long block48b = expansion_permutation(block32b);
    block48b ^= key48b;
    block32b = substitutions(block48b);
    return permutation(block32b);
}

unsigned long long DES::expansion_permutation(unsigned long block32b) {
    unsigned long long block48b = 0;
    for (char unsigned i = 0; i < 48; ++i) {
        block48b |= (unsigned long long) ((block32b >> (32 - __EP[i])) & 0x01) << (63 - i);
    }
    return block48b;
}

unsigned long DES::substitutions(unsigned long long block48b) {
    char unsigned blocks4b[4], blocks6b[8] = {0};
    split_48bits_to_6bits(block48b, blocks6b);
    substitution_6bits_to_4bits(blocks6b, blocks4b);
    return join_4bits_to_32bits(blocks4b);
}

unsigned long DES::permutation(unsigned long block32b) {
    unsigned long new_block32b = 0;
    for (char unsigned i = 0; i < 32; ++i) {
        new_block32b |= ((block32b >> (32 - __P[i])) & 0x01) << (31 - i);
    }
    return new_block32b;
}

void DES::split_48bits_to_6bits(unsigned long long block48b, char unsigned *blocks6b) {
    for (char unsigned i = 0; i < 8; ++i) {
        blocks6b[i] = (block48b >> (58 - (i * 6))) << 2;
    }
}

void DES::substitution_6bits_to_4bits(char unsigned *blocks6b, char unsigned *blocks4b) {
    char unsigned block2b, block4b;

    for (char unsigned i = 0, j = 0; i < 8; i += 2, ++j) {
        block2b = extreme_bits(blocks6b[i]);
        block4b = middle_bits(blocks6b[i]);
        blocks4b[j] = __Sbox[i][block2b][block4b];

        block2b = extreme_bits(blocks6b[i + 1]);
        block4b = middle_bits(blocks6b[i + 1]);
        blocks4b[j] = (blocks4b[j] << 4) | __Sbox[i + 1][block2b][block4b];
    }
}

unsigned long DES::join_4bits_to_32bits(char unsigned *blocks4b) {
    unsigned long block32b;
    for (char unsigned *p = blocks4b; p < blocks4b + 4; ++p) {
        block32b = (block32b << 8) | *p;
    }
    return block32b;
}

char unsigned DES::extreme_bits(char unsigned block6b) {
    return ((block6b >> 6) & 0x2) | ((block6b >> 2) & 0x1);
}

char unsigned DES::middle_bits(char unsigned block6b) {
    return (block6b >> 3) & 0xF;
}

void DES::split_64bits_to_8bits(unsigned long long block64b, char unsigned *blocks8b) {
    for (unsigned i = 0; i < 8; ++i) {
        blocks8b[i] = (char unsigned) (block64b >> ((7 - i) * 8));
    }
}

unsigned long long DES::final_permutation(unsigned long long block64b) {
    unsigned long long new_block64b = 0;
    for (char unsigned i = 0; i < 64; ++i) {
        new_block64b |= ((block64b >> (64 - __FP[i])) & 0x01) << (63 - i);
    }
    return new_block64b;
}

inline unsigned long long DES::join_32bits_to_64bits(unsigned long block32b_1, unsigned long block32b_2) {
    unsigned long long block64b;
    block64b = (unsigned long long) block32b_1;
    block64b = (unsigned long long) (block64b << 32) | block32b_2;
    return block64b;
}