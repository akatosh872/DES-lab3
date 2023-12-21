#include "../include/DesEncryptor.h"


DesEncryptor::DesEncryptor(unsigned long long int key1, unsigned long long int key2, unsigned long long int key3) {
    DesKey1 = key1;
    DesKey2 = key2;
    DesKey3 = key3;
}

void DesEncryptor::encrypt(FileHandler &fh, bool mode, DesMode des_mode, unsigned long long iv)
{
    char unsigned buffer[FILE_CHUNK_SIZE];
    char unsigned crypted[FILE_CHUNK_SIZE];
    unsigned long long keys[3][16] = {0};
    unsigned bytesRead;

    key_expansion(DesKey1, keys[0]);
    key_expansion(DesKey2, keys[1]);
    key_expansion(DesKey3, keys[2]);

    while (fh.readChunk(buffer, FILE_CHUNK_SIZE, bytesRead))
    {
        des.des_encrypt_block(crypted, mode, bytesRead, buffer, keys[0], iv);
        iv = *(unsigned long long*)crypted;
        if (des_mode != DES_ONE) {
            bool mode2 = (des_mode == DES_EEE) ? mode : !mode;
            des.des_encrypt_block(crypted, mode2, bytesRead, crypted, keys[1], iv);
            iv = *(unsigned long long*)crypted;
            des.des_encrypt_block(crypted, mode, bytesRead, crypted, keys[2], iv);
            iv = *(unsigned long long*)crypted;
        }
        fh.writeChunk(crypted, bytesRead);
    }
}

void DesEncryptor::key_expansion(unsigned long long key64b, unsigned long long *keys48b) {
    unsigned long K1 = 0, K2 = 0;
    key_permutation_56bits_to_28bits(key64b, &K1, &K2);
    key_expansion_to_48bits(K1, K2, keys48b);
}

void DesEncryptor::key_permutation_56bits_to_28bits(unsigned long long block56b, unsigned long *block28b_1, unsigned long *block28b_2) {
    for (char unsigned i = 0; i < 28; ++i) {
        *block28b_1 |= ((block56b >> (64 - __K1P[i])) & 0x01) << (31 - i);
        *block28b_2 |= ((block56b >> (64 - __K2P[i])) & 0x01) << (31 - i);
    }
}

void DesEncryptor::key_expansion_to_48bits(unsigned long block28b_1, unsigned long block28b_2, unsigned long long *keys48b) {
    unsigned long long block56b;
    char unsigned n;

//        Розподіляємо розмір зміщення бітів
    for (char unsigned i = 0; i < 16; ++i) {
        switch (i) {
            case 0:
            case 1:
            case 8:
            case 15:
                n = 1;
                break;
            default:
                n = 2;
                break;
        }

        block28b_1 = LSHIFT_28BIT(block28b_1, n);
        block28b_2 = LSHIFT_28BIT(block28b_2, n);
        block56b = join_28bits_to_56bits(block28b_1, block28b_2);
        keys48b[i] = key_contraction_permutation(block56b);
    }
}

inline unsigned long long DesEncryptor::join_28bits_to_56bits(unsigned long block28b_1, unsigned long block28b_2) {
    unsigned long long block56b;
    block56b = (block28b_1 >> 4);
    block56b = ((block56b << 32) | block28b_2) << 4;
    return block56b;
}

unsigned long long DesEncryptor::key_contraction_permutation(unsigned long long block56b) {
    unsigned long long block48b = 0;
    for (char unsigned i = 0; i < 48; ++i) {
        block48b |= ((block56b >> (64 - __CP[i])) & 0x01) << (63 - i);
    }
    return block48b;
}