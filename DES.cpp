#include "DES.h"

    void DES::des_encrypt(uint8_t *to, uint8_t mode, size_t length, uint8_t *from, uint64_t key64b) {
        length = length % 8 == 0 ? length : length + (8 - (length % 8));

        uint64_t keys48b[16] = {0};
        uint32_t N1, N2;

        key_expansion(key64b, keys48b);


        for (size_t i = 0; i < length; i += 8) {
            split_64bits_to_32bits(
                    initial_permutation(
                            join_8bits_to_64bits(from + i)
                    ),
                    &N1, &N2
            );
            feistel_cipher(mode, &N1, &N2, keys48b);
            split_64bits_to_8bits(
                    final_permutation(
                            join_32bits_to_64bits(N2, N1)
                    ),
                    (to + i)
            );
        }
    }

    void DES::key_expansion(uint64_t key64b, uint64_t *keys48b) {
        uint32_t K1 = 0, K2 = 0;
        key_permutation_56bits_to_28bits(key64b, &K1, &K2);
        key_expansion_to_48bits(K1, K2, keys48b);
    }

/**
*    Об'єднує масив з 8 байтів у 64-бітне ціле число
*/
    uint64_t DES::join_8bits_to_64bits(uint8_t *blocks8b) {
        uint64_t block64b;
        for (uint8_t *p = blocks8b; p < blocks8b + 8; ++p) {
            block64b = (block64b << 8) | *p;
        }
        return block64b;
    }

/**
*    Розділяє ключ на 2 28 бітних частини, та виконує перестановку за таблицею __KP
*/
    void DES::key_permutation_56bits_to_28bits(uint64_t block56b, uint32_t *block28b_1, uint32_t *block28b_2) {
        for (uint8_t i = 0; i < 28; ++i) {
            *block28b_1 |= ((block56b >> (64 - __K1P[i])) & 0x01) << (31 - i);
            *block28b_2 |= ((block56b >> (64 - __K2P[i])) & 0x01) << (31 - i);
        }
    }

/**
 *   Об'єднує 2 28 бітні частини в один 56-бітний блок
 */
    void DES::key_expansion_to_48bits(uint32_t block28b_1, uint32_t block28b_2, uint64_t *keys48b) {
        uint64_t block56b;
        uint8_t n;

//        Розподіляємо розмір зміщення бітів
        for (uint8_t i = 0; i < 16; ++i) {
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

/**
 *  Розширення 28-бітного числа до 56 біт
 */
    uint64_t DES::join_28bits_to_56bits(uint32_t block28b_1, uint32_t block28b_2) {
        uint64_t block56b;
        block56b = (block28b_1 >> 4);
        block56b = ((block56b << 32) | block28b_2) << 4;
        return block56b;
    }

/**
 * Виконує перестановку скорочення ключів для отримання 48-бітного ключа з 56-бітного
*/
    uint64_t DES::key_contraction_permutation(uint64_t block56b) {
        uint64_t block48b = 0;
        for (uint8_t i = 0; i < 48; ++i) {
            block48b |= ((block56b >> (64 - __CP[i])) & 0x01) << (63 - i);
        }
        return block48b;
    }

/**
 *  Розділяє 64-бітне число на 2 32-бітні
 */
    void DES::split_64bits_to_32bits(uint64_t block64b, uint32_t *block32b_1, uint32_t *block32b_2) {
        *block32b_1 = (uint32_t) (block64b >> 32);
        *block32b_2 = (uint32_t) (block64b);
    }

/**
 *  Початкове кодування перед функцією
 */
    uint64_t DES::initial_permutation(uint64_t block64b) {
        uint64_t new_block64b = 0;
        for (uint8_t i = 0; i < 64; ++i) {
            new_block64b |= ((block64b >> (64 - __IP[i])) & 0x01) << (63 - i);
        }
        return new_block64b;
    }

/**
 *  Метод отримує режим (кодування або декодування), та 16 раундів повторює функцію
 */

    void DES::feistel_cipher(uint8_t mode, uint32_t *N1, uint32_t *N2, uint64_t *keys48b) {
        switch (mode) {
            case 'E': {
                for (int8_t round = 0; round < 16; ++round) {
                    round_feistel_cipher(N1, N2, keys48b[round]);
                }
                std::swap(N1, N2);
                break;
            }
            case 'D': {
                for (int8_t round = 15; round >= 0; --round) {
                    round_feistel_cipher(N1, N2, keys48b[round]);
                }
                std::swap(N1, N2);
                break;
            }
        }
    }

/**
 *  Метод викликає функцію кодування та змінює дві частини до наступного раунду
 */
    void DES::round_feistel_cipher(uint32_t *N1, uint32_t *N2, uint64_t key48b) {
        uint32_t temp = *N2;
        *N2 = func_F(*N2, key48b) ^ *N1;
        *N1 = temp;
    }

/**
 *  Головна функція F в алгоритмі DES.
 */
    uint32_t DES::func_F(uint32_t block32b, uint64_t key48b) {
        uint64_t block48b = expansion_permutation(block32b);
        block48b ^= key48b;
        block32b = substitutions(block48b);
        return permutation(block32b);
    }

/**
 *  Розширення 32-біт до 48-біт
 */
    uint64_t DES::expansion_permutation(uint32_t block32b) {
        uint64_t block48b = 0;
        for (uint8_t i = 0; i < 48; ++i) {
            block48b |= (uint64_t) ((block32b >> (32 - __EP[i])) & 0x01) << (63 - i);
        }
        return block48b;
    }

/**
 *  Розподіл 48-біт на 8 частин по 6-біт
 */
    uint32_t DES::substitutions(uint64_t block48b) {
        uint8_t blocks4b[4], blocks6b[8] = {0};
        split_48bits_to_6bits(block48b, blocks6b);
        substitution_6bits_to_4bits(blocks6b, blocks4b);
        return join_4bits_to_32bits(blocks4b);
    }

/**
 *  Виконує остаточну перестановку на 32-бітному блоці
 */
    uint32_t DES::permutation(uint32_t block32b) {
        uint32_t new_block32b = 0;
        for (uint8_t i = 0; i < 32; ++i) {
            new_block32b |= ((block32b >> (32 - __P[i])) & 0x01) << (31 - i);
        }
        return new_block32b;
    }

/**
 *  Розподіл 48-біт на 8 частин по 6-біт
 */
    void DES::split_48bits_to_6bits(uint64_t block48b, uint8_t *blocks6b) {
        for (uint8_t i = 0; i < 8; ++i) {
            blocks6b[i] = (block48b >> (58 - (i * 6))) << 2;
        }
    }

/**
 *  Переставляє 6-бітні блоки в 4-бітні блоки за допомогою таблиць підстановки.
 */
    void DES::substitution_6bits_to_4bits(uint8_t *blocks6b, uint8_t *blocks4b) {
        uint8_t block2b, block4b;

        for (uint8_t i = 0, j = 0; i < 8; i += 2, ++j) {
            block2b = extreme_bits(blocks6b[i]);
            block4b = middle_bits(blocks6b[i]);
            blocks4b[j] = __Sbox[i][block2b][block4b];

            block2b = extreme_bits(blocks6b[i + 1]);
            block4b = middle_bits(blocks6b[i + 1]);
            blocks4b[j] = (blocks4b[j] << 4) | __Sbox[i + 1][block2b][block4b];
        }
    }

/**
 *  Об'єднання 4-бітних блоків до одного 32-бітного
 */
    uint32_t DES::join_4bits_to_32bits(uint8_t *blocks4b) {
        uint32_t block32b;
        for (uint8_t *p = blocks4b; p < blocks4b + 4; ++p) {
            block32b = (block32b << 8) | *p;
        }
        return block32b;
    }

/**
 * Виділяє старші біти з 6-бітного блоку
 */
    uint8_t DES::extreme_bits(uint8_t block6b) {
        return ((block6b >> 6) & 0x2) | ((block6b >> 2) & 0x1);
    }

/**
 * Виділяє середні біти з 6-бітного блоку.
 */
    uint8_t DES::middle_bits(uint8_t block6b) {
        return (block6b >> 3) & 0xF;
    }

/**
 *  Розділ 64-бітного блоку до 8-бітних
 */
    void DES::split_64bits_to_8bits(uint64_t block64b, uint8_t *blocks8b) {
        for (size_t i = 0; i < 8; ++i) {
            blocks8b[i] = (uint8_t) (block64b >> ((7 - i) * 8));
        }
    }

/**
 *  Кінцева перестановка
 */
    uint64_t DES::final_permutation(uint64_t block64b) {
        uint64_t new_block64b = 0;
        for (uint8_t i = 0; i < 64; ++i) {
            new_block64b |= ((block64b >> (64 - __FP[i])) & 0x01) << (63 - i);
        }
        return new_block64b;
    }

/**
 *  Об'єднання 32-бітних частин до 64-бітної
 */
    uint64_t DES::join_32bits_to_64bits(uint32_t block32b_1, uint32_t block32b_2) {
        uint64_t block64b;
        block64b = (uint64_t) block32b_1;
        block64b = (uint64_t) (block64b << 32) | block32b_2;
        return block64b;
    }