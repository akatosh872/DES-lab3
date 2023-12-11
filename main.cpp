#include <windows.h>
#include <iostream>
#include "include/DES.h"
#include "include/DesEncryptor.h"
#include "include/FileHandler.h"
#include "include/UserInterface.h"


int main() {
    uint64_t key1, key2, key3, iv = 0;
    char crypt_mode;
    DesMode des_mode;

    UserInterface userInterface;

    userInterface.InitializeDesKeys(key1, key2, key3);
    userInterface.EnterIVHex(iv);

    FileHandler fh(userInterface.getInputFileName(), userInterface.getOutputFileName());
    crypt_mode = userInterface.getCrypt() == 'E';
    des_mode = userInterface.getDES();
    DesEncryptor des{};

    if (fh.openInputFile() && fh.openOutputFile()) {

        DWORD start_time = GetTickCount();
        des.encrypt(fh, crypt_mode, des_mode, iv, key1, key2, key3);
        DWORD end_time = GetTickCount();

        DWORD elapsed_time = end_time - start_time;
        printf("Execution time: %.3f seconds\n", elapsed_time / 1000.0);

        fh.closeInputFile();
        fh.closeOutputFile();
    }

    return 0;
}