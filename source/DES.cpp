#include "../include/DES.h"

#pragma GCC optimize ("unroll-loops")
#pragma once

void DES::des_encrypt_block(char unsigned *to, bool mode, char unsigned *from, unsigned long long *keys48b) {
    unsigned long long block64b = 0;
    for (int j = 0; j < 8; ++j) {
        block64b |= static_cast<unsigned long long>(from[j]) << ((7 - j) * 8);
    }

    unsigned long N1 = (initial_permutation(block64b) >> 32);
    unsigned long N2 = (initial_permutation(block64b));

    feistel_cipher(mode, &N1, &N2, keys48b);
    unsigned long long processed_block = final_permutation((static_cast<unsigned long long>(N2) << 32) | N1);

    for (unsigned i = 0; i < 8; ++i) {
        to[i] = (processed_block >> ((7 - i) * 8)) & 0xFF;
    }
}

inline unsigned long long DES::initial_permutation(unsigned long long block64b) {
    unsigned long long new_block64b = 0;
    for (char unsigned i = 0; i < 64; ++i) {
        new_block64b |= ((block64b >> (64 - __IP[i])) & 0x01) << (63 - i);
    }
    return new_block64b;
}

inline void DES::feistel_cipher(bool mode, unsigned long *N1, unsigned long *N2, unsigned long long *keys48b) {
    int inc = mode ? 1 : -1;
    for (signed round = mode ? 0 : 15; round >= 0 && round < 16; round += inc) {
        round_feistel_cipher(N1, N2, keys48b[round]);
    }
}

void DES::round_feistel_cipher(unsigned long *N1, unsigned long *N2, unsigned long long key48b) {
    unsigned long temp = *N2;
    *N2 = func_F(*N2, key48b) ^ *N1;
    *N1 = temp;
}

inline unsigned long DES::func_F(unsigned long block32b, unsigned long long key48b) {
    unsigned long long block48b = expansion_permutation(block32b) ^ key48b;
    return permutation(substitutions(block48b));
}

inline unsigned long long DES::expansion_permutation(unsigned long block32b) {
    unsigned long long block48b = 0;
    for (char unsigned i = 0; i < 48; ++i) {
        block48b |= (static_cast<unsigned long long>(block32b >> (32 - __EP[i])) & 0x01) << (63 - i);
    }
    return block48b;
}

inline unsigned long DES::substitutions(unsigned long long block48b) {
    char unsigned blocks4b[4], blocks6b[8] = {0};
    split_48bits_to_6bits(block48b, blocks6b);
    substitution_6bits_to_4bits(blocks6b, blocks4b);
    return join_4bits_to_32bits(blocks4b);
}

inline unsigned long DES::permutation(unsigned long block32b) {
    unsigned long new_block32b = 0;
    for (char unsigned i = 0; i < 32; ++i) {
        new_block32b |= ((block32b >> (32 - __P[i])) & 0x01) << (31 - i);
    }
    return new_block32b;
}

inline void DES::split_48bits_to_6bits(unsigned long long block48b, char unsigned *blocks6b) {
    for (char unsigned i = 0; i < 8; ++i) {
        blocks6b[i] = (block48b >> (58 - (i * 6))) << 2;
    }
}

inline void DES::substitution_6bits_to_4bits(char unsigned *blocks6b, char unsigned *blocks4b) {
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

inline unsigned long DES::join_4bits_to_32bits(char unsigned *blocks4b) {
    unsigned long block32b = 0;
    for (char unsigned *p = blocks4b; p < blocks4b + 4; ++p) {
        block32b = (block32b << 8) | *p;
    }
    return block32b;
}

inline char unsigned DES::extreme_bits(char unsigned block6b) {
    return ((block6b >> 6) & 0x2) | ((block6b >> 2) & 0x1);
}

inline char unsigned DES::middle_bits(char unsigned block6b) {
    return (block6b >> 3) & 0xF;
}

inline unsigned long long DES::final_permutation(unsigned long long block64b) {
    unsigned long long new_block64b = 0;
    for (char unsigned i = 0; i < 64; ++i) {
        new_block64b |= ((block64b >> (64 - __FP[i])) & 0x01) << (63 - i);
    }
    return new_block64b;
}