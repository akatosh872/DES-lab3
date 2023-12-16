#ifndef UNTITLED_DES_H
#define UNTITLED_DES_H

#include <cstdint>
#include "MatrixConst.h"
#include <iostream>

#define LSHIFT_28BIT(x, L) ((((x) << (L)) | ((x) >> (-(L) & 27))) & (((uint64_t)1 << 32) - 1));

class DES {
public:
    DES() = default;

    void des_encrypt_block(uint8_t *to, bool mode, size_t length, uint8_t *from, uint64_t key64b, uint64_t iv);
    void key_expansion(uint64_t key64b, uint64_t *keys48b);
    uint64_t join_8bits_to_64bits(uint8_t *blocks8b);
    void key_permutation_56bits_to_28bits(uint64_t block56b, uint32_t *block28b_1, uint32_t *block28b_2);
    void key_expansion_to_48bits(uint32_t block28b_1, uint32_t block28b_2, uint64_t *keys48b);
    uint64_t join_28bits_to_56bits(uint32_t block28b_1, uint32_t block28b_2);
    uint64_t key_contraction_permutation(uint64_t block56b);
    void split_64bits_to_32bits(uint64_t block64b, uint32_t *block32b_1, uint32_t *block32b_2);
    uint64_t initial_permutation(uint64_t block64b);
    void feistel_cipher(bool mode, uint32_t *N1, uint32_t *N2, uint64_t *keys48b);
    void round_feistel_cipher(uint32_t *N1, uint32_t *N2, uint64_t key48b);
    uint32_t func_F(uint32_t block32b, uint64_t key48b);
    uint64_t expansion_permutation(uint32_t block32b);
    uint32_t substitutions(uint64_t block48b);
    uint32_t permutation(uint32_t block32b);
    void split_48bits_to_6bits(uint64_t block48b, uint8_t *blocks6b);
    void substitution_6bits_to_4bits(uint8_t *blocks6b, uint8_t *blocks4b);
    uint32_t join_4bits_to_32bits(uint8_t *blocks4b);
    uint8_t extreme_bits(uint8_t block6b);
    uint8_t middle_bits(uint8_t block6b);
    void split_64bits_to_8bits(uint64_t block64b, uint8_t *blocks8b);
    uint64_t final_permutation(uint64_t block64b);
    uint64_t join_32bits_to_64bits(uint32_t block32b_1, uint32_t block32b_2);
};

#endif //UNTITLED_DES_H