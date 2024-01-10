#ifndef UNTITLED_FILEHANDLER_H
#define UNTITLED_FILEHANDLER_H

#pragma once
#include <fstream>
#include <iostream>
#include "windows.h"

class FileHandler {
public:
    FileHandler(const char* inputFileName, const char* outputFileName);
    bool openInputFile();
    bool openOutputFile();
    void closeInputFile();
    void closeOutputFile();
    bool readChunk(char unsigned* buffer, unsigned chunkSize, unsigned& bytesRead);
    void writeChunk(const char unsigned* buffer, unsigned chunkSize);

private:
    const char* inputFileName;
    const char* outputFileName;
    std::ifstream fileInput;
    std::ofstream fileOutput;
};

#endif //UNTITLED_FILEHANDLER_H
