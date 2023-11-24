#include "CImageBank.h"

std::vector<uint8_t> CImageBank::AndroidMode3ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha) {
    std::vector<uint8_t> colorArray;
    colorArray.resize(width * height * 4);
    int stride = width * 4;
    int position = 0;
    int pad = GetPadding(width, 3, 4, true);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
                colorArray[y * stride + x * 4 + 2] = imageData[position];
                colorArray[y * stride + x * 4 + 1] = imageData[position + 1];
                colorArray[y * stride + x * 4 + 0] = imageData[position + 2];
                colorArray[y * stride + x * 4 + 3] = 255;
                position += 3;
        }

        position += pad;

    }
    return colorArray;
}

std::vector<uint8_t> CImageBank::AndroidMode0ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha) {
    std::vector<uint8_t> colorArray;
    colorArray.resize(width * height * 4);
    int stride = width * 4;
    int position = 0;
    int pad = GetPadding(width, 4);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
                colorArray[y * stride + x * 4 + 2] = imageData[position];
                colorArray[y * stride + x * 4 + 1] = imageData[position + 1];
                colorArray[y * stride + x * 4 + 0] = imageData[position + 2];
                colorArray[y * stride + x * 4 + 3] = imageData[position + 3];
                position += 4;
        }

        position += pad * 3;

    }
    return colorArray;
}

std::vector<uint8_t> CImageBank::AndroidMode4ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha) {
    std::vector<uint8_t> colorArray;
    colorArray.resize(width * height * 4);
    int stride = width * 4;
    int position = 0;
    int pad = GetPadding(width, 3);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint16_t newShort = (uint16_t)(imageData[position] | (imageData[position + 1] << 8));

            char r = ((newShort & 0xF800) >> 11);
            char g = ((newShort & 0x7E0) >> 5);
            char b = (newShort & 0x1F);

            r = (r << 3);
            g = (g << 2);
            b = (b << 3);

            colorArray[y * stride + x * 4 + 2] = r;
            colorArray[y * stride + x * 4 + 1] = g;
            colorArray[y * stride + x * 4 + 0] = b;
            colorArray[y * stride + x * 4 + 3] = 255;

            position += 2;
        }
    
        position += pad * 2;
    }
    return colorArray;
}

void CImageBank::preload() {
    uint16_t numImages = readShort(*file, offset);
    std::cout << numImages << " images" << std::endl;
    
    bool is = true;
    
    
    images.resize(numImages);
    for(int i = 0; i < numImages; i++)
        images[i] = std::make_unique<BankSlot>();
    
    uint16_t numBmp = readShort(*file, offset);
    
    for(int i = 0; i < numBmp; i++) {
        images[readShort(*file, offset)]->dataOffset = offset;
        // std::cout << offset << std::endl;
        //Debug
        // offset+=4;
        // std::cout << "Mode: " <<  << std::endl;
        int mode = readInt(*file, offset);
        int width = readShort(*file, offset);
        int height = readShort(*file, offset);
        
        offset+=8;
        
        uint32_t size = readInt(*file, offset);
        
        // uint8_t iscomp = readByte(*file, offset);
        
        // offset--;
        
        std::vector<unsigned char> out = decompress(readBytes(*file, offset, size));
        
        // std::cout << iscomp << std::endl;
        // if(i == 500) is = false;
        // offset+=size;
        // if(!is) {
        std::ofstream outFile("images/"+std::to_string(i)+".rgba");
        switch(mode) {
            case 0:
                out = AndroidMode0ToRGBA(out, width, height, false);
                break;
            case 3:
                out = AndroidMode3ToRGBA(out, width, height, false);
                break;
            default:
                std::cerr << "Invalid mode." << std::endl;
                break;
        }
        
        for (const auto &e : out) outFile << e;
        is = true;
        // std::cout << width << " e " << height << std::endl;
        // }
    }
}
