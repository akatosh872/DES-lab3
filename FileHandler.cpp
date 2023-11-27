#include "FileHandler.h"

const char *inputFileName;
const char *outputFileName;
std::ifstream fileInput;
std::ofstream fileOutput;

FileHandler::FileHandler(const char *inputFileName, const char *outputFileName) : inputFileName(inputFileName), outputFileName(outputFileName) {}

bool FileHandler::openInputFile() {
    fileInput.open(inputFileName, std::ios::binary);
    return fileInput.is_open();
}

bool FileHandler::openOutputFile() {
    fileOutput.open(outputFileName, std::ios::binary);
    return fileOutput.is_open();
}

void FileHandler::closeInputFile() {
    fileInput.close();
}

void FileHandler::closeOutputFile() {
    fileOutput.close();
}

size_t FileHandler::getBytesRead() {
    return fileInput.gcount();
}

bool FileHandler::readChunk(uint8_t *buffer, size_t chunkSize) {
    fileInput.read(reinterpret_cast<char *>(buffer), chunkSize);
    return !fileInput.eof();
}

void FileHandler::writeChunk(const uint8_t *buffer, size_t chunkSize) {
    fileOutput.write(reinterpret_cast<const char *>(buffer), chunkSize);
}

