#ifndef UNTITLED_DESINPUTHANDLER_H
#define UNTITLED_DESINPUTHANDLER_H


#include "InputHandler.h"

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

class DESInputHandler : public InputHandler {
public:
    void setDesMode ();
    void initializeDesKeys(uint64_t& key1, uint64_t& key2, uint64_t& key3);
    void requestKey(std::string keyMessage, uint64_t &key);
    bool isWeakKey(uint64_t key);
    bool getCrypt() const;
    DesMode getDES() const;
private:
    int des_mode{};
};


#endif //UNTITLED_DESINPUTHANDLER_H
