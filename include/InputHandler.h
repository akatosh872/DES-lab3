#ifndef UNTITLED_INPUTHANDLER_H
#define UNTITLED_INPUTHANDLER_H

#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <cstdio>
#include <tchar.h>
#include <conio.h>

#include "DesEncryptor.h"


class InputHandler {
public:
    InputHandler();
    void setCryptMode();
    void initializeFileSelection(OPENFILENAME& file, const char* filter, char* fileName);
    const char* getInputFileName() const;
    const char* getOutputFileName() const;
    inline void delChar();
    bool EnterPasswordHex(unsigned long long& key);
    bool enterIVHex(unsigned long long& iv);

    char crypt_mode{};
private:
    OPENFILENAME input_file{};
    OPENFILENAME out_file{};
    char szFileNameInput[MAX_PATH] = "";
    char szFileNameOutput[MAX_PATH] = "";

    static const char BACK_SPACE = 8;
    static const char DELTA_HEX = 7;
    static const char BASE = 16;
    static const char ENTER = 13;
};



#endif //UNTITLED_INPUTHANDLER_H
