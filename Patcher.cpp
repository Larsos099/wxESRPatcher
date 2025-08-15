

#include "Patcher.hpp"
#include "defines.hpp"

void Patcher::readPosition(std::fstream &file, std::array<char, (2048)> &buffer, size_t position) {
    file.seekg(static_cast<long long>(position), std::ios::beg);
    file.read(buffer.data(), LBA_SIZE);
}

void Patcher::writePosition(std::fstream &file, const std::array<char, (2048)> &buffer, size_t position) {
    file.seekp(static_cast<long long>(position), std::ios::beg);
    file.write(buffer.data(), LBA_SIZE);
}

unsigned int Patcher::patch(const std::vector<std::string> &params) {
    if (params.empty()) {
        return 97;
    }
    const fs::path filePath(params[0]);
    std::array<char, LBA_SIZE> buffer{};
    char checksum{};
    unsigned short i = 0;
    bool is_udf = false;
    unsigned short *desc_crc = nullptr;
    unsigned short desc_crc_len;
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("File couldn't be opened");
    for (i = 1; i < 64; i++) {
        readPosition(file, buffer, LBA_SIZE * i + 32768);

        if (std::string_view(buffer.data() + 1, 3) == "NSR") {
            is_udf = true;
            break;
        }
    }

    if (!is_udf) {
        file.close();
        throw std::runtime_error("Not an UDF file");
    }

    readPosition(file, buffer, 14 * LBA_SIZE);

    if (std::string_view(buffer.data() + 25, 4) == "+NSR") {
        file.close();
        throw std::runtime_error("Already patched");
    }

    readPosition(file, buffer, 34 * LBA_SIZE);

    writePosition(file, buffer, 14 * LBA_SIZE);

    readPosition(file, buffer, 50 * LBA_SIZE);

    writePosition(file, buffer, 15 * LBA_SIZE);

    readPosition(file, buffer, 34 * LBA_SIZE);

    buffer[0xBC] = static_cast<char>(0x80);
    buffer[0xBD] = static_cast<char>(0x00);

    desc_crc_len = *reinterpret_cast<unsigned short*>(buffer.data() + 10);
    desc_crc = reinterpret_cast<unsigned short *>(buffer.data() + 8);

    *desc_crc = crc_itu_t(0, (buffer.data() + 16), desc_crc_len);

    checksum = 0;

    for (i = 0; i < 4; i++)
        checksum += buffer[i];

    for (i = 5; i < 16; i++)
        checksum += buffer[i];

    buffer[4] = checksum;

    writePosition(file, buffer, 34 * LBA_SIZE);

    readPosition(file, buffer, 50 * LBA_SIZE);

    buffer[0xBC] = static_cast<char>(0x80);
    buffer[0xBD] = static_cast<char>(0x00);

    desc_crc_len = *reinterpret_cast<unsigned short*>(buffer.data() + 10);
    desc_crc = reinterpret_cast<unsigned short *>(buffer.data() + 8);

    *desc_crc = crc_itu_t(0, (buffer.data() + 16), desc_crc_len);

    checksum = 0;

    for (i = 0; i < 4; i++)
        checksum += buffer[i];

    for (i = 5; i < 16; i++)
        checksum += buffer[i];

    buffer[4] = checksum;

    writePosition(file, buffer, 50 * LBA_SIZE);

    file.seekg(128 * LBA_SIZE, std::ios::beg);
    file.write(reinterpret_cast<const char *>(dvdvdata.data()), dvdvdata.size());
    std::cout << "Applied ESR successfully!" << std::endl;
    file.close();
    return 0;
}

unsigned int Patcher::unpatch(const std::vector<std::string> &params) {
    if (params.empty()) {
        return 97;
    }
    try {
        Patcher::isPatched(params);
    } catch (const std::exception &ex) {
        if (std::string_view(ex.what()).contains("File is not ESR Patched")) {
            throw;
        }

    }
    std::array<char, LBA_SIZE> buffer{};
    fs::path filePath(params[0]);
    unsigned short i = 0;
    bool is_udf = false;
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("File couldn't be opened");

    for (i = 1; i < 64; i++) {
        readPosition(file, buffer, LBA_SIZE * i + 32768);
        if (std::string_view(buffer.data() + 1, 3) == "NSR") {
            is_udf = true;
            break;
        }
    }
    if (!is_udf) {
        file.close();
        throw std::runtime_error("File is not an UDF File.");
    }

    readPosition(file, buffer, 14 * LBA_SIZE);
    writePosition(file, buffer, LBA_SIZE);
    readPosition(file, buffer, 34 * LBA_SIZE);
    writePosition(file, buffer, LBA_SIZE);
    std::fill_n(buffer.begin(), LBA_SIZE, 0);
    writePosition(file, buffer, 14 * LBA_SIZE);
    writePosition(file, buffer, 15 * LBA_SIZE);
    for (int i = 0; i < 12; i++) {
        writePosition(file, buffer, (128 + i) * LBA_SIZE);

    }
    file.close();
    std::cout << "Removed ESR successfully!" << std::endl;
    return 0;
}

unsigned short Patcher::crc_itu_t_byte(const unsigned short crc, const unsigned char data) {
    return (crc << 8) ^ crc_itu_t_table[((crc >> 8) ^ data) & 0xff];
}

unsigned short Patcher::crc_itu_t(unsigned short crc, const char *buffer, size_t len) {
    while (len--)
        crc = crc_itu_t_byte(crc, *buffer++);
    return crc;
}


unsigned int Patcher::isPatched(const std::vector<std::string> &params) {
    std::fstream file(params[0], std::ios::in | std::ios::out | std::ios::binary);
    std::array<char, LBA_SIZE> _buf{};
    readPosition(file, _buf, 14 * LBA_SIZE);

    if (std::string_view(_buf.data() + 25, 4) == "+NSR") {
        file.close();
        throw std::runtime_error("Already patched");
    }
    else {
        file.close();
        throw std::runtime_error("File is not ESR Patched");
    }
    return 0;
}
