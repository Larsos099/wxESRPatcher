

#ifndef PATCHER_HPP
#define PATCHER_HPP

#include <memory>
#include <filesystem>
#include <fstream>
#include <exception>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <array>

#include "defines.hpp"

namespace fs = std::filesystem;
class Patcher final {

    static void readPosition(std::fstream &file, std::array<char, LBA_SIZE> &buffer, size_t position);
    static void writePosition(std::fstream &file, const std::array<char, LBA_SIZE> &buffer, size_t position);

    static unsigned short crc_itu_t_byte(unsigned short crc, unsigned char data);
    static unsigned short crc_itu_t(unsigned short crc, const char* buffer, size_t len);

    public:
    Patcher() = delete;
    static unsigned int isPatched(const std::vector<std::string> &params);
    static unsigned int patch(const std::vector<std::string> &params);
    static unsigned int unpatch(const std::vector<std::string> &params);
};




#endif // PATCHER_HPP