#include <iostream>
#include <chrono>
#include "include/DES.h"
#include "include/DesEncryptor.h"
#include "include/FileHandler.h"
#include "include/UserInterface.h"

using namespace std;

int main() {
    uint64_t key1, key2, key3;
    char crypt_mode;
    DesMode des_mode;

    UserInterface userInterface;
    userInterface.getFileSelection();

    printf("Enter password 1: ");
    userInterface.EnterPasswordHex(key1);

    if (userInterface.getDES() != DesMode::DES_ONE) {
        printf("Enter password 2: ");
        userInterface.EnterPasswordHex(key2);
        printf("Enter password 2: ");
        userInterface.EnterPasswordHex(key3);
    }

    FileHandler fh(userInterface.getInputFileName(), userInterface.getOutputFileName());
    DesEncryptor des{};
    crypt_mode = userInterface.getCrypt();
    des_mode = userInterface.getDES();

    if (fh.openInputFile() && fh.openOutputFile()) {

        auto start_time = chrono::high_resolution_clock::now();
        des.encrypt(fh, (crypt_mode == 'E'), des_mode, key1, key2, key3);
        auto end_time = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed_time = end_time - start_time;
        cout << "Execution time: " << elapsed_time.count() << " seconds" << endl;

        fh.closeInputFile();
        fh.closeOutputFile();
    }

    return 0;
}