#include "../include/FileHandler.h"

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

bool FileHandler::readChunk(uint8_t *buffer, size_t chunkSize, size_t& bytesRead) {
    fileInput.read(reinterpret_cast<char *>(buffer), chunkSize);
    bytesRead = fileInput.gcount();
    return bytesRead > 0;
}

void FileHandler::writeChunk(const uint8_t *buffer, size_t chunkSize) {
    fileOutput.write(reinterpret_cast<const char *>(buffer), chunkSize);
}

