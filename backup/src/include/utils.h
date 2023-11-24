#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cassert>
#include <string>
#include <cmath>

#include <zlib.h>

#define CHUNK_LAST 32639

inline std::vector<uint8_t> LoadFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return std::vector<uint8_t>();
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();

    std::vector<uint8_t> buffer(fileSize);

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    file.close();

    return buffer;
}

inline std::vector<uint8_t> readBytes(std::vector<uint8_t>& buffer, size_t& offset, int count) {
    if (offset >= buffer.size()) {
        std::cerr << "Invalid offset: " << offset << std::endl;
        return std::vector<uint8_t>();
    }
    size_t bytesToRead = std::min(static_cast<size_t>(count), buffer.size() - offset);

    std::vector<uint8_t> result(bytesToRead);

    for (size_t i = 0; i < bytesToRead; ++i) {
        result[i] = buffer[offset + i];
    }
    offset += count;
    return result;
}

inline uint8_t readByte(std::vector<uint8_t>& buffer, size_t& offset) {
    if (offset >= buffer.size()) {
        std::cerr << "Invalid offset: " << offset << std::endl;
        return 0;
    }
    size_t bytesToRead = std::min(static_cast<size_t>(1), buffer.size() - offset);

    offset += 1;
    return buffer[offset - 1];
}

inline uint16_t readShort(std::vector<uint8_t>& buffer, size_t& offset) {
    if (offset >= buffer.size()) {
        std::cerr << "Invalid offset: " << offset << std::endl;
        return 0;
    }
    
    size_t bytesToRead = std::min(static_cast<size_t>(2), buffer.size() - offset);

    std::vector<uint16_t> result(bytesToRead);

    for (size_t i = 0; i < bytesToRead; ++i) {
        result[i] = buffer[offset + i];
    }
    offset += 2;
    
    return (uint16_t)(result[0] | (result[1] << 8));
}

inline uint32_t readInt(std::vector<uint8_t>& buffer, size_t& offset) {
    uint8_t readUnsignedByte = readByte(buffer, offset);
    uint8_t readUnsignedByte2 = readByte(buffer, offset);
    uint8_t readUnsignedByte3 = readByte(buffer, offset);
    uint8_t readUnsignedByte4 = readByte(buffer, offset);
    
    // uint32_t result = (16777216 * readUnsignedByte3) + (65536 * readUnsignedByte4) + (readUnsignedByte2 * 256) + readUnsignedByte;
    uint32_t result = readUnsignedByte + 256U*readUnsignedByte2 + 65536U*readUnsignedByte3 + 16777216U*readUnsignedByte4;
    
    return result;
}

inline uint32_t readColor(std::vector<uint8_t>& buffer, size_t& offset) {
    uint8_t readUnsignedByte = readByte(buffer, offset);
    uint8_t readUnsignedByte2 = readByte(buffer, offset);
    uint8_t readUnsignedByte3 = readByte(buffer, offset);
    readByte(buffer, offset);
    
    uint32_t result = (65536 * readUnsignedByte) + (readUnsignedByte2 * 256) + readUnsignedByte3;
    return result;
}

inline void readChar(std::vector<uint8_t>& buffer, size_t& offset, std::vector<uint8_t>& array) {
    for (int i = 0; i < array.size(); i++) {
        array[i] = ((readByte(buffer, offset) * 256) + readByte(buffer, offset));
    }
}

inline std::string readString(std::vector<uint8_t>& buffer, size_t& offset) {
    std::string result = "";
    //no non-unicode support for now...
    
    size_t filePointer = offset;
    
    while (readShort(buffer, offset) != 0) {};
    
    size_t filePointer3 = offset;
    
    offset = filePointer;

    if (filePointer3 > (filePointer + 2)) {
        std::vector<uint8_t> cArr;
        cArr.resize((( ((filePointer3 - filePointer) - 1))));
        for(int x = 0; x < cArr.size(); x++)
            result += readByte(buffer, offset);
    }
    offset += 2;
    
    return result;
}

inline std::vector<unsigned char> decompress(const std::vector<unsigned char>& compressed_data) {
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    if (inflateInit(&stream) != Z_OK) {
        std::cerr << "Error initializing zlib inflate" << std::endl;
        return std::vector<unsigned char>();
    }

    stream.avail_in = compressed_data.size();
    stream.next_in = const_cast<unsigned char*>(compressed_data.data());

    std::vector<unsigned char> decompressed_data;
    while (true) {
        unsigned char buffer[4096];

        stream.avail_out = sizeof(buffer);
        stream.next_out = buffer;

        int ret = inflate(&stream, Z_NO_FLUSH);
        if (ret == Z_STREAM_END) {
            decompressed_data.insert(decompressed_data.end(), buffer, buffer + sizeof(buffer) - stream.avail_out);
            break;
        } else if (ret != Z_OK) {
            std::cerr << "Error decompressing data: " << ret << std::endl;
            inflateEnd(&stream);
            return std::vector<unsigned char>();
        }

        decompressed_data.insert(decompressed_data.end(), buffer, buffer + sizeof(buffer) - stream.avail_out);
    }
    
    inflateEnd(&stream);

    return decompressed_data;
}

inline int GetPadding(int width, int pointSize, int bytes = 2, bool modular = false) {
    if (modular) return (bytes - width * pointSize % bytes) % bytes;

    int pad = bytes - width * pointSize % bytes;
    if (pad == bytes) return 0;

    return (int)std::ceil(pad / (float)pointSize);
}
#endif
