#include "../include/UserInterface.h"

const uint64_t weakKeys[] = {
        0x0101010101010101,
        0xFEFEFEFEFEFEFEFE,
        0x1F1F1F1F0E0E0E0E,
        0xE0E0E0E0F1F1F1F1,
        0x01FE01FE01FE01FE,
        0x1FE01FE01FE01FE0,
        0x01E001E001F101F1,
        0x1FFE1FFE0EFE0EFE,
        0x011F011F010E010E,
        0xE0FEE0FEF1FEF1FE,
        0xFE01FE01FE01FE01,
        0xE0F1E0F1E0F1E0F1,
        0xE001E001F101F101,
        0xFE1FFE1FFE0EFE0E,
        0x1F011F010E010E01,
        0xFEE0FEE0FEF1FEF1
};

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

    MessageBox(NULL, "Select the file you want to encrypt/decrypt", "Attention", MB_ICONEXCLAMATION);
    GetOpenFileName(&input_file);

    MessageBox(NULL, "Select the file where to save", "Attention", MB_ICONEXCLAMATION);
    GetSaveFileName(&out_file);
}

void UserInterface::initializeFileSelection(OPENFILENAME& file, const char* filter, char* fileName) {
    file.lStructSize = sizeof(file);
    file.hwndOwner = GetConsoleWindow();
    file.lpstrFilter = filter;
    file.lpstrFile = fileName;
    file.nMaxFile = MAX_PATH;
    file.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

void UserInterface::InitializeDesKeys(uint64_t &key1, uint64_t &key2, uint64_t &key3) {
    if (des_mode == 1) {
        requestKey("64-bit password", key1);
    } else if (des_mode == 2 || des_mode == 3) {
        requestKey("64-bit password 1", key1);
        requestKey("64-bit password 2", key2);
        requestKey("64-bit password 3", key3);
    } else {
        throw std::runtime_error("Unexpected DES mode");
    }
}

void UserInterface::requestKey(std::string keyMessage, uint64_t &key) {
    printf(("Enter " + keyMessage + ": ").c_str());
    EnterPasswordHex(key);
    while(isWeakKey(key)){
        printf(("Invalid " + keyMessage + ", it's a weak key. Enter again: ").c_str());
        EnterPasswordHex(key);
    }
}

bool UserInterface::isWeakKey(uint64_t key) {

    for (const auto& weakKey : weakKeys) {
        if (key == weakKey) {
            std::cout << "Weak key detected" << std::endl;
            return true;
        }
    }

    return false;
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

bool UserInterface::EnterIVHex(uint64_t &iv) {
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
            DelChar();
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
