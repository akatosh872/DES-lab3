#include <cstdint>
#include "MatrixConst.h"
#include <iostream>
#include "FileHandler.h"

#ifndef UNTITLED_DES_H
#define UNTITLED_DES_H

#define LSHIFT_28BIT(x, L) ((((x) << (L)) | ((x) >> (-(L) & 27))) & (((uint64_t)1 << 32) - 1))

class DES {
public:
    void des_encrypt(FileHandler& fh, uint8_t mode, uint64_t key64b);

    void des_encrypt_block(uint8_t *to, uint8_t mode, size_t length, uint8_t *from, uint64_t key64b);

    void key_expansion(uint64_t key64b, uint64_t *keys48b);

/**
*    Об'єднує масив з 8 байтів у 64-бітне ціле число
*/
    uint64_t join_8bits_to_64bits(uint8_t *blocks8b);

/**
*    Розділяє ключ на 2 28 бітних частини, та виконує перестановку за таблицею __KP
*/
    void key_permutation_56bits_to_28bits(uint64_t block56b, uint32_t *block28b_1, uint32_t *block28b_2);

/**
 *   Об'єднує 2 28 бітні частини в один 56-бітний блок
 */
    void key_expansion_to_48bits(uint32_t block28b_1, uint32_t block28b_2, uint64_t *keys48b);

/**
 *  Розширення 28-бітного числа до 56 біт
 */
    uint64_t join_28bits_to_56bits(uint32_t block28b_1, uint32_t block28b_2);

/**
 * Виконує перестановку скорочення ключів для отримання 48-бітного ключа з 56-бітного
*/
    uint64_t key_contraction_permutation(uint64_t block56b);

/**
 *  Розділяє 64-бітне число на 2 32-бітні
 */
    void split_64bits_to_32bits(uint64_t block64b, uint32_t *block32b_1, uint32_t *block32b_2);

/**
 *  Початкове кодування перед функцією
 */
    uint64_t initial_permutation(uint64_t block64b);

/**
 *  Метод отримує режим (кодування або декодування), та 16 раундів повторює функцію
 */

    void feistel_cipher(uint8_t mode, uint32_t *N1, uint32_t *N2, uint64_t *keys48b);

/**
 *  Метод викликає функцію кодування та змінює дві частини до наступного раунду
 */
    void round_feistel_cipher(uint32_t *N1, uint32_t *N2, uint64_t key48b);

/**
 *  Головна функція F в алгоритмі DES.
 */
    uint32_t func_F(uint32_t block32b, uint64_t key48b);

/**
 *  Розширення 32-біт до 48-біт
 */
    uint64_t expansion_permutation(uint32_t block32b);

/**
 *  Розподіл 48-біт на 8 частин по 6-біт
 */
    uint32_t substitutions(uint64_t block48b);

/**
 *  Виконує остаточну перестановку на 32-бітному блоці
 */
    uint32_t permutation(uint32_t block32b);

/**
 *  Розподіл 48-біт на 8 частин по 6-біт
 */
    void split_48bits_to_6bits(uint64_t block48b, uint8_t *blocks6b);

/**
 *  Переставляє 6-бітні блоки в 4-бітні блоки за допомогою таблиць підстановки.
 */
    void substitution_6bits_to_4bits(uint8_t *blocks6b, uint8_t *blocks4b);

/**
 *  Об'єднання 4-бітних блоків до одного 32-бітного
 */
    uint32_t join_4bits_to_32bits(uint8_t *blocks4b);

/**
 * Виділяє старші біти з 6-бітного блоку
 */
    uint8_t extreme_bits(uint8_t block6b);

/**
 * Виділяє середні біти з 6-бітного блоку.
 */
    uint8_t middle_bits(uint8_t block6b);

/**
 *  Розділ 64-бітного блоку до 8-бітних
 */
    void split_64bits_to_8bits(uint64_t block64b, uint8_t *blocks8b);

/**
 *  Кінцева перестановка
 */
    uint64_t final_permutation(uint64_t block64b);

/**
 *  Об'єднання 32-бітних частин до 64-бітної
 */
    uint64_t join_32bits_to_64bits(uint32_t block32b_1, uint32_t block32b_2);
};


#endif //UNTITLED_DES_H
