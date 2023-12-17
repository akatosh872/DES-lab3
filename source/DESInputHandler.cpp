#include "../include/DESInputHandler.h"

void DESInputHandler::setDesMode()
{
    char buffer[256];
    do {
        printf("Select DES crypt mode: (1) DES, (2) 3DES-EEE3, (3) 3DES-EDE3: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &des_mode);
    } while (des_mode < 1 || des_mode > 3);
}

void DESInputHandler::initializeDesKeys(unsigned long long &key1, unsigned long long &key2, unsigned long long &key3) {
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

void DESInputHandler::requestKey(std::string keyMessage, unsigned long long &key) {
    printf(("Enter " + keyMessage + ": ").c_str());
    EnterPasswordHex(key);
    while(isWeakKey(key)){
        printf(("Invalid " + keyMessage + ", it's a weak key. Enter again: ").c_str());
        EnterPasswordHex(key);
    }
}

bool DESInputHandler::isWeakKey(unsigned long long key) {

    for (const auto& weakKey : weakKeys) {
        if (key == weakKey) {
            std::cout << "Weak key detected" << std::endl;
            return true;
        }
    }

    return false;
}

bool DESInputHandler::getCrypt() const {
    return crypt_mode == 'E';
}

DesMode DESInputHandler::getDES() const {
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
