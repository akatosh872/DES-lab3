#include <windows.h>
#include <iostream>
#include "include/DesEncryptor.h"
#include "include/FileHandler.h"
#include "include/DESInputHandler.h"


int main() {
    unsigned long long key1, key2, key3, iv = 0;
    bool crypt_mode;
    DesMode des_mode;

    DESInputHandler inputHandler;

    inputHandler.setDesMode();
    inputHandler.setCryptMode();
    inputHandler.initializeDesKeys(key1, key2, key3);
    inputHandler.enterIVHex(iv);

    FileHandler fh(inputHandler.getInputFileName(), inputHandler.getOutputFileName());
    crypt_mode = inputHandler.getCrypt();
    des_mode = inputHandler.getDES();
    DesEncryptor des{key1, key2, key3};

    if (fh.openInputFile() && fh.openOutputFile()) {
        DWORD start_time = GetTickCount();
        crypt_mode ? des.encrypt(fh, crypt_mode, des_mode, iv) : des.decrypt(fh, crypt_mode, des_mode, iv);
        DWORD end_time = GetTickCount();

        DWORD elapsed_time = end_time - start_time;
        printf("Execution time: %.3f seconds\n", elapsed_time / 1000.0);

        fh.closeInputFile();
        fh.closeOutputFile();
    }
    system("pause");
    return 0;
}