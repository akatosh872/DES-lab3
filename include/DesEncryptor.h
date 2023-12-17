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
};

#endif //UNTITLED_DESENCRYPTOR_H
