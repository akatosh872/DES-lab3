#include "../include/DesEncryptor.h"

const size_t FILE_CHUNK_SIZE = 131072;

void DesEncryptor::encrypt(FileHandler &fh, bool mode, DesMode des_mode, uint64_t key1, uint64_t key2, uint64_t key3)
{
    uint8_t buffer[FILE_CHUNK_SIZE];
    uint8_t crypted[FILE_CHUNK_SIZE];
    size_t bytesRead;

    while (fh.readChunk(buffer, FILE_CHUNK_SIZE, bytesRead))
    {
        encrypt_chunk(mode, des_mode, bytesRead, buffer, crypted, key1, key2, key3);
        fh.writeChunk(crypted, bytesRead);
    }
}

void DesEncryptor::encrypt_chunk(bool mode, DesMode des_mode, size_t bytes, uint8_t *buffer, uint8_t *crypted, uint64_t key1, uint64_t key2, uint64_t key3)
{
    des.des_encrypt_block(crypted, mode, bytes, buffer, key1);

    switch(des_mode)
    {
        case DES_ONE:
            break;
        case DES_EEE:
            des.des_encrypt_block(crypted, mode, bytes, crypted, key2);
            des.des_encrypt_block(crypted, mode, bytes, crypted, key3);
            break;
        case DES_EDE:
            des.des_encrypt_block(crypted, !mode, bytes, crypted, key2);
            des.des_encrypt_block(crypted, mode, bytes, crypted, key3);
            break;
    }
}