#ifndef UNTITLED_DESENCRYPTOR_H
#define UNTITLED_DESENCRYPTOR_H


#include "DES.h"
#include "FileHandler.h"

enum DesMode {
    DES_ONE,
    DES_EEE,
    DES_EDE
};

class DesEncryptor
{
private:
    DES des;
    unsigned long long DesKey1;
    unsigned long long DesKey2;
    unsigned long long DesKey3;

public:
    DesEncryptor(unsigned long long key1, unsigned long long key2, unsigned long long key3);
    void encrypt(FileHandler &fh, bool mode, DesMode des_mode, unsigned long long iv);
    void key_expansion(unsigned long long key64b, unsigned long long *keys48b);
    void key_permutation_56bits_to_28bits(unsigned long long block56b, unsigned long *block28b_1, unsigned long *block28b_2);
    void key_expansion_to_48bits(unsigned long block28b_1, unsigned long block28b_2, unsigned long long *keys48b);
    unsigned long long join_28bits_to_56bits(unsigned long block28b_1, unsigned long block28b_2);
    unsigned long long key_contraction_permutation(unsigned long long block56b);
};

#endif //UNTITLED_DESENCRYPTOR_H
