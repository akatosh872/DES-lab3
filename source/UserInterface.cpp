#include "../include/UserInterface.h"

UserInterface::UserInterface() {
    char buffer[256];
    do {
        printf("Enter mode (E/D): ");
        fgets(buffer, sizeof(buffer), stdin);
        crypt_mode = buffer[0];
        crypt_mode = toupper(crypt_mode);
    } while (!(crypt_mode == 'E' || crypt_mode == 'D'));

    do {
        printf("Select DES crypt mode: (1) DES, (2) 3DES-EEE3, (3) 3DES-EDE3: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &des_mode);
    } while (des_mode < 1 || des_mode > 3);

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
    MessageBox(NULL, "Select the file you want to encrypt/decrypt", "Attention", MB_ICONEXCLAMATION);
    GetOpenFileName(&input_file);

    MessageBox(NULL, "Select the file where to save", "Attention", MB_ICONEXCLAMATION);
    GetSaveFileName(&out_file);
}

inline void UserInterface::DelChar()
{
    putchar(BACK_SPACE);
    putchar(' ');
    putchar(BACK_SPACE);
}

bool UserInterface::EnterPasswordHex(uint64_t &key) {
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
            DelChar();
            EnteredAmount--;
        }
    } while (!(EnteredAmount == 16 && CurrentChar == ENTER));
    putchar('\n');

    for (EnteredAmount = 0, key = 0; EnteredAmount < 16; key = key * BASE + Password[EnteredAmount++]);
    delete[]Password;

    return true;
}


const char *UserInterface::getInputFileName() const {
    return input_file.lpstrFile;
}

const char *UserInterface::getOutputFileName() const {
    return out_file.lpstrFile;
}

char UserInterface::getCrypt() const {
    return crypt_mode;
}

DesMode UserInterface::getDES() const {
    switch (des_mode) {
        case 1:
            return DesMode::DES_ONE;
        case 2:
            return DesMode::DES_EEE;
        case 3:
            return DesMode::DES_EDE;
        default:
            throw std::runtime_error("Unexpected DES mode");
    }
}
