#include <Windows.h>
#include <commdlg.h>
#include <iostream>
#include <cstdio>
#include <tchar.h>
#include <conio.h>
#include <cstdint>

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

    bool EnterPasswordHex(const TCHAR* Prompt, uint64_t& Res, unsigned PasswordLen);

    void getFileSelection();

    char getMode() const;

private:
    OPENFILENAME input_file{};
    OPENFILENAME out_file{};
    char szFileNameInput[MAX_PATH] = "";
    char szFileNameOutput[MAX_PATH] = "";
    char mode{};
};



#endif //UNTITLED_USERINTERFACE_H
