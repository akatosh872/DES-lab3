#include "../include/DesEncryptor.h"

const size_t FILE_CHUNK_SIZE = 131072;

void DesEncryptor::encrypt(FileHandler &fh, bool mode, DesMode des_mode, uint64_t iv, uint64_t key1, uint64_t key2, uint64_t key3)
{
    uint8_t buffer[FILE_CHUNK_SIZE];
    uint8_t crypted[FILE_CHUNK_SIZE];
    size_t bytesRead;

    while (fh.readChunk(buffer, FILE_CHUNK_SIZE, bytesRead))
    {
        des.des_encrypt_block(crypted, mode, bytesRead, buffer, key1, iv);

        switch(des_mode)
        {
            case DES_ONE:
                break;
            case DES_EEE:
                des.des_encrypt_block(crypted, mode, bytesRead, crypted, key2, iv);
                des.des_encrypt_block(crypted, mode, bytesRead, crypted, key3, iv);
                break;
            case DES_EDE:
                des.des_encrypt_block(crypted, !mode, bytesRead, crypted, key2, iv);
                des.des_encrypt_block(crypted, mode, bytesRead, crypted, key3, iv);
                break;
        }
        fh.writeChunk(crypted, bytesRead);
    }
}