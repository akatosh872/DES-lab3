#include <cstdio>
#include <cstdint>
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <chrono>
#include "DES.h"
#include "FileHandler.h"
#include "KeyInput.h"

using namespace std;

OPENFILENAME input_file;
OPENFILENAME out_file;
HWND hWnd = GetConsoleWindow();  // Отримати вказівник на вікно консолі
char szFileNameInput[MAX_PATH] = "";  // Масив для зберігання імені файлу
char szFileNameOutput[MAX_PATH] = "";

const size_t FILE_CHUNK_SIZE = 131072;

int main() {
    uint8_t crypted[FILE_CHUNK_SIZE];
    uint8_t buffer[FILE_CHUNK_SIZE];
    size_t bytesRead;
    uint64_t Res64;
    char mode;

    input_file.lStructSize = out_file.lStructSize = sizeof(input_file);
    input_file.hwndOwner = out_file.hwndOwner = hWnd;
    input_file.lpstrFilter = out_file.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    input_file.lpstrFile = szFileNameInput;
    out_file.lpstrFile = szFileNameOutput;
    input_file.nMaxFile = out_file.nMaxFile = MAX_PATH;
    input_file.Flags = out_file.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    // Вибір режиму шифрування або дешифрування
    cout << "Choose program mode: E - encrypt, D - decrypt" << endl;
    do {
        cout << "Enter mode (E/D): ";
        cin >> mode;
    } while (mode != 'E' && mode != 'D');

    KeyInput KI;
    KI.EnterPasswordHex(__TEXT("Enter the password"), Res64, 16);

    // Вибір файлу для обробки
    MessageBox(NULL, "Select the file you want to encrypt/decrypt", "Attention", MB_ICONEXCLAMATION);
    GetOpenFileName(&input_file);

    // Вибір файлу для збереження результату
    MessageBox(NULL, "Select the file where to save", "Attention", MB_ICONEXCLAMATION);
    GetSaveFileName(&out_file);

    // Створення екземплярів
    DES des;
    FileHandler fh(input_file.lpstrFile, out_file.lpstrFile);

    if (fh.openInputFile() && fh.openOutputFile()) {
        fh.readChunk(buffer, FILE_CHUNK_SIZE);
        bytesRead = fh.getBytesRead();

        auto start_time = chrono::high_resolution_clock::now();
        des.des_encrypt(crypted, mode, bytesRead, buffer, Res64);
        auto end_time = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed_time = end_time - start_time;
        cout << "Execution time: " << elapsed_time.count() << " seconds" << endl;

        fh.writeChunk(crypted, bytesRead);

        fh.closeInputFile();
        fh.closeOutputFile();
    }

    return 0;
}