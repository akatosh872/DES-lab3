#ifndef UNTITLED_DESENCRYPTOR_H
#define UNTITLED_DESENCRYPTOR_H


#include "../include/DES.h"
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

public:
    void encrypt(FileHandler &fh, bool mode, DesMode des_mode, uint64_t key1, uint64_t key2, uint64_t key3);
    void encrypt_chunk(bool mode, DesMode des_mode, size_t bytes, uint8_t *buffer, uint8_t *crypted, uint64_t key1, uint64_t key2, uint64_t key3);
};

#endif //UNTITLED_DESENCRYPTOR_H
