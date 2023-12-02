#include <windows.h>
#include <iostream>
#include <chrono>
#include "DES.h"
#include "FileHandler.h"
#include "UserInterface.h"

using namespace std;

int main() {
    uint64_t key64;
    char mode;

    UserInterface userInterface;
    userInterface.getFileSelection();
    userInterface.EnterPasswordHex(__TEXT("Enter the password"), key64, 16);

    FileHandler fh(userInterface.getInputFileName(), userInterface.getOutputFileName());
    DES des;
    mode = userInterface.getMode();

    if (fh.openInputFile() && fh.openOutputFile()) {

        auto start_time = chrono::high_resolution_clock::now();
        des.des_encrypt(fh, mode, key64);
        auto end_time = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed_time = end_time - start_time;
        cout << "Execution time: " << elapsed_time.count() << " seconds" << endl;

        fh.closeInputFile();
        fh.closeOutputFile();
    }

    return 0;
}