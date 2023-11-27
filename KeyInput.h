#ifndef UNTITLED_KEYINPUT_H
#define UNTITLED_KEYINPUT_H

typedef unsigned long long NUM_TYPE;

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <windows.h>
#include <cstdint>

#define BACK_SPACE	8
#define DELTA_HEX	7
#define BASE		16
#define ENTER		13

class KeyInput {
public:
    inline void DelChar();

    bool EnterPasswordHex(const TCHAR* Prompt, uint64_t& Res, unsigned PasswordLen);

};


#endif //UNTITLED_KEYINPUT_H
