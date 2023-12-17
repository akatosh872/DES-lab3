#include "../include/DesEncryptor.h"

const unsigned FILE_CHUNK_SIZE = 131072;

DesEncryptor::DesEncryptor(unsigned long long int key1, unsigned long long int key2, unsigned long long int key3) {
    DesKey1 = key1;
    DesKey2 = key2;
    DesKey3 = key3;
}

void DesEncryptor::encrypt(FileHandler &fh, bool mode, DesMode des_mode, unsigned long long iv)
{
    char unsigned buffer[FILE_CHUNK_SIZE];
    char unsigned crypted[FILE_CHUNK_SIZE];
    unsigned bytesRead;

    while (fh.readChunk(buffer, FILE_CHUNK_SIZE, bytesRead))
    {
        des.des_encrypt_block(crypted, mode, bytesRead, buffer, DesKey1, iv);

        switch(des_mode)
        {
            case DES_ONE:
                break;
            case DES_EEE:
                des.des_encrypt_block(crypted, mode, bytesRead, crypted, DesKey2, iv);
                des.des_encrypt_block(crypted, mode, bytesRead, crypted, DesKey3, iv);
                break;
            case DES_EDE:
                des.des_encrypt_block(crypted, !mode, bytesRead, crypted, DesKey2, iv);
                des.des_encrypt_block(crypted, mode, bytesRead, crypted, DesKey3, iv);
                break;
        }
        fh.writeChunk(crypted, bytesRead);
    }
}