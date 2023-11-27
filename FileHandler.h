#include <cstdint>
#include <fstream>
#include <iostream>

#ifndef UNTITLED_FILEHANDLER_H
#define UNTITLED_FILEHANDLER_H


class FileHandler {
public:
    FileHandler(const char* inputFileName, const char* outputFileName);

    bool openInputFile();

    bool openOutputFile();

    void closeInputFile();

    void closeOutputFile();

    size_t getBytesRead();

    bool readChunk(uint8_t* buffer, size_t chunkSize);

    void writeChunk(const uint8_t* buffer, size_t chunkSize);

private:
    const char* inputFileName;
    const char* outputFileName;
    std::ifstream fileInput;
    std::ofstream fileOutput;
};



#endif //UNTITLED_FILEHANDLER_H
