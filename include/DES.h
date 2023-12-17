#ifndef UNTITLED_DES_H
#define UNTITLED_DES_H

#include "MatrixConst.h"
#include <iostream>

const unsigned FILE_CHUNK_SIZE = 131072;
#define LSHIFT_28BIT(x, L) ((((x) << (L)) | ((x) >> (-(L) & 27))) & (((unsigned long long)1 << 32) - 1));

class DES {
public:
    DES() = default;

    void des_encrypt_block(char unsigned *to, bool mode, unsigned length, char unsigned *from, unsigned long long key64b, unsigned long long iv);
    void key_expansion(unsigned long long key64b, unsigned long long *keys48b);
    unsigned long long join_8bits_to_64bits(char unsigned *blocks8b);
    void key_permutation_56bits_to_28bits(unsigned long long block56b, unsigned long *block28b_1, unsigned long *block28b_2);
    void key_expansion_to_48bits(unsigned long block28b_1, unsigned long block28b_2, unsigned long long *keys48b);
    unsigned long long join_28bits_to_56bits(unsigned long block28b_1, unsigned long block28b_2);
    unsigned long long key_contraction_permutation(unsigned long long block56b);
    void split_64bits_to_32bits(unsigned long long block64b, unsigned long *block32b_1, unsigned long *block32b_2);
    unsigned long long initial_permutation(unsigned long long block64b);
    void feistel_cipher(bool mode, unsigned long *N1, unsigned long *N2, unsigned long long *keys48b);
    void round_feistel_cipher(unsigned long *N1, unsigned long *N2, unsigned long long key48b);
    unsigned long func_F(unsigned long block32b, unsigned long long key48b);
    unsigned long long expansion_permutation(unsigned long block32b);
    unsigned long substitutions(unsigned long long block48b);
    unsigned long permutation(unsigned long block32b);
    void split_48bits_to_6bits(unsigned long long block48b, char unsigned *blocks6b);
    void substitution_6bits_to_4bits(char unsigned *blocks6b, char unsigned *blocks4b);
    unsigned long join_4bits_to_32bits(char unsigned *blocks4b);
    char unsigned extreme_bits(char unsigned block6b);
    char unsigned middle_bits(char unsigned block6b);
    void split_64bits_to_8bits(unsigned long long block64b, char unsigned *blocks8b);
    unsigned long long final_permutation(unsigned long long block64b);
    unsigned long long join_32bits_to_64bits(unsigned long block32b_1, unsigned long block32b_2);
};

#endif //UNTITLED_DES_H
