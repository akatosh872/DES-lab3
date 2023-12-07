#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <cstdio>
#include <tchar.h>
#include <conio.h>
#include <cstdint>
#include "DES.h"

#ifndef UNTITLED_USERINTERFACE_H
#define UNTITLED_USERINTERFACE_H

#define BACK_SPACE	8
#define DELTA_HEX	7
#define BASE		16
#define ENTER		13

class UserInterface {
public:
    UserInterface();

    void initializeFileSelection(OPENFILENAME& file, const char* filter, char* fileName);

    const char* getInputFileName() const;

    const char* getOutputFileName() const;

    inline void DelChar();

    bool EnterPasswordHex(uint64_t& key);

    void getFileSelection();

    char getCrypt() const;

    DesMode getDES() const;

private:
    OPENFILENAME input_file{};
    OPENFILENAME out_file{};
    char szFileNameInput[MAX_PATH] = "";
    char szFileNameOutput[MAX_PATH] = "";
    char crypt_mode{};
    int des_mode{};
};



#endif //UNTITLED_USERINTERFACE_H
