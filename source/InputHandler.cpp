#include "../include/InputHandler.h"


InputHandler::InputHandler() {
    // Ініціалізація структур
    initializeFileSelection(input_file, "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0", szFileNameInput);
    initializeFileSelection(out_file, "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0", szFileNameOutput);

    MessageBox(NULL, "Select the file you want to encrypt/decrypt", "Attention", MB_ICONEXCLAMATION);
    GetOpenFileName(&input_file);

    MessageBox(NULL, "Select the file where to save", "Attention", MB_ICONEXCLAMATION);
    GetSaveFileName(&out_file);
}

void InputHandler::setCryptMode()
{
    char buffer[256];
    do {
        printf("Enter mode (E/D): ");
        fgets(buffer, sizeof(buffer), stdin);
        crypt_mode = buffer[0];
        crypt_mode = toupper(crypt_mode);
    } while (!(crypt_mode == 'E' || crypt_mode == 'D'));
}

void InputHandler::initializeFileSelection(OPENFILENAME& file, const char* filter, char* fileName) {
    file.lStructSize = sizeof(file);
    file.hwndOwner = GetConsoleWindow();
    file.lpstrFilter = filter;
    file.lpstrFile = fileName;
    file.nMaxFile = MAX_PATH;
    file.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

inline void InputHandler::delChar()
{
    putchar(BACK_SPACE);
    putchar(' ');
    putchar(BACK_SPACE);
}

bool InputHandler::EnterPasswordHex(uint64_t &key) {
    unsigned EnteredAmount = 0;
    char *Password, CurrentChar;

    Password = new char[16];
    do {
        CurrentChar = toupper(_getch());
        if ((CurrentChar >= '0' && CurrentChar <= '9') || (CurrentChar >= 'A' && CurrentChar <= 'F')) {
            if (EnteredAmount < 16) {
                putchar(CurrentChar);
                if (CurrentChar > '9')
                    CurrentChar -= DELTA_HEX;
                Password[EnteredAmount++] = CurrentChar - '0';
            }
        } else if (CurrentChar == BACK_SPACE && EnteredAmount > 0) {
            delChar();
            EnteredAmount--;
        }
    } while (!(EnteredAmount == 16 && CurrentChar == ENTER));
    putchar('\n');

    for (EnteredAmount = 0, key = 0; EnteredAmount < 16; key = key * BASE + Password[EnteredAmount++]);
    delete[]Password;

    return true;
}

bool InputHandler::enterIVHex(uint64_t &iv) {
    const unsigned IVSize = 16;
    unsigned enteredAmount = 0;
    char *ivHexChars = new char[IVSize];
    char currentChar;

    printf("Enter initial vector to CBC mode (press enter to ebc mode): ");
    do {
        currentChar = toupper(_getch());
        if ((currentChar >= '0' && currentChar <= '9') || (currentChar >= 'A' && currentChar <= 'F')) {
            if (enteredAmount < IVSize) {
                putchar(currentChar);
                if (currentChar > '9')
                    currentChar -= DELTA_HEX;
                ivHexChars[enteredAmount++] = currentChar - '0';
            }
        } else if (currentChar == BACK_SPACE && enteredAmount > 0) {
            delChar();
            enteredAmount--;
        }
    } while (!((enteredAmount == 16 || enteredAmount == 0) && currentChar == ENTER));
    putchar('\n');

    if(enteredAmount == 0) { // no iv entered
        delete[] ivHexChars;
        return false;
    }

    for (enteredAmount = 0, iv = 0; enteredAmount < IVSize; iv = iv * BASE + ivHexChars[enteredAmount++]);
    delete[] ivHexChars;

    return true;
}

const char *InputHandler::getInputFileName() const {
    return input_file.lpstrFile;
}

const char *InputHandler::getOutputFileName() const {
    return out_file.lpstrFile;
}