#include "UserInterface.h"

UserInterface::UserInterface() {
    do {
        std::cout << "Enter mode (E/D): ";
        std::cin >> mode;
    } while (mode != 'E' && mode != 'D');

    // Ініціалізація структур
    initializeFileSelection(input_file, "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0", szFileNameInput);
    initializeFileSelection(out_file, "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0", szFileNameOutput);
}

void UserInterface::initializeFileSelection(OPENFILENAME& file, const char* filter, char* fileName) {
    file.lStructSize = sizeof(file);
    file.hwndOwner = GetConsoleWindow();
    file.lpstrFilter = filter;
    file.lpstrFile = fileName;
    file.nMaxFile = MAX_PATH;
    file.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

void UserInterface::getFileSelection() {
    // Выбор файла для обработки
    MessageBox(NULL, "Select the file you want to encrypt/decrypt", "Attention", MB_ICONEXCLAMATION);
    GetOpenFileName(&input_file);

    // Выбор файла для сохранения результата
    MessageBox(NULL, "Select the file where to save", "Attention", MB_ICONEXCLAMATION);
    GetSaveFileName(&out_file);
}

inline void UserInterface::DelChar()
{
    putchar(BACK_SPACE);
    putchar(' ');
    putchar(BACK_SPACE);
}

bool UserInterface::EnterPasswordHex(const TCHAR* Prompt, uint64_t& Res, unsigned PasswordLen){

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


const char *UserInterface::getInputFileName() const {
    return input_file.lpstrFile;
}

const char *UserInterface::getOutputFileName() const {
    return out_file.lpstrFile;
}

char UserInterface::getMode() const {
    return mode;
}
