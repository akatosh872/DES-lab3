#ifndef UNTITLED_FILEHANDLER_H
#define UNTITLED_FILEHANDLER_H

#include <cstdint>
#include <fstream>
#include <iostream>

class FileHandler {
public:
    FileHandler(const char* inputFileName, const char* outputFileName);
    bool openInputFile();
    bool openOutputFile();
    void closeInputFile();
    void closeOutputFile();
    bool readChunk(uint8_t* buffer, size_t chunkSize, size_t& bytesRead);
    void writeChunk(const uint8_t* buffer, size_t chunkSize);

private:
    const char* inputFileName;
    const char* outputFileName;
    std::ifstream fileInput;
    std::ofstream fileOutput;
};

#endif //UNTITLED_FILEHANDLER_H
