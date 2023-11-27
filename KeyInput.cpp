#include "KeyInput.h"

inline void KeyInput::DelChar()
{
    putchar(BACK_SPACE);
    putchar(' ');
    putchar(BACK_SPACE);
}

bool KeyInput::EnterPasswordHex(const TCHAR* Prompt, uint64_t& Res, unsigned PasswordLen){

    unsigned EnteredAmount = 0;
    char* Password, CurrentChar;

    if (PasswordLen > 0)
    {
        Password = new char[PasswordLen];
        _tprintf(__TEXT("%s (%i hex digits). Press Enter to stop afrer entering %i hex digits (BackSpace for deleting digits):\n"), Prompt, PasswordLen, PasswordLen);
        do
        {
            CurrentChar = toupper(_getch());
            if ((CurrentChar >= '0' && CurrentChar <= '9') || (CurrentChar >= 'A' && CurrentChar <= 'F'))
            {
                if (EnteredAmount < PasswordLen)
                {
                    putchar(CurrentChar);
                    if (CurrentChar > '9')
                        CurrentChar -= DELTA_HEX;
                    Password[EnteredAmount++] = CurrentChar - '0';
                }
            }
            else
            if (CurrentChar == BACK_SPACE && EnteredAmount > 0)
            {
                DelChar();
                EnteredAmount--;
            }
        } while (!(EnteredAmount == PasswordLen && CurrentChar == ENTER));
        putchar('\n');

            for (EnteredAmount = 0, Res = 0; EnteredAmount < PasswordLen; Res = Res * BASE + Password[EnteredAmount++]);
            delete[]Password;

        return true;
    }
    return false;
}