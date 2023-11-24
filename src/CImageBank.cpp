#include "CImageBank.h"

std::vector<uint8_t> CImageBank::AndroidMode3ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha) {
    std::vector<uint8_t> colorArray;
    colorArray.resize(width * height * 4);
    int stride = width * 4;
    int position = 0;
    int pad = GetPadding(width, 3, 4, true);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
                colorArray[y * stride + x * 4 + 0] = imageData[position];
                colorArray[y * stride + x * 4 + 1] = imageData[position + 1];
                colorArray[y * stride + x * 4 + 2] = imageData[position + 2];
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
                colorArray[y * stride + x * 4 + 0] = imageData[position];
                colorArray[y * stride + x * 4 + 1] = imageData[position + 1];
                colorArray[y * stride + x * 4 + 2] = imageData[position + 2];
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

            colorArray[y * stride + x * 4 + 0] = r;
            colorArray[y * stride + x * 4 + 1] = g;
            colorArray[y * stride + x * 4 + 2] = b;
            colorArray[y * stride + x * 4 + 3] = 255;

            position += 2;
        }
    
        position += pad * 2;
    }
    return colorArray;
}

std::vector<uint8_t> CImageBank::AndroidMode1ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha) {
    std::vector<uint8_t> colorArray;
    colorArray.resize(width * height * 4);
    int stride = width * 4;
    int position = 0;
    int pad = GetPadding(width, 3);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint16_t newShort = (imageData[position] | (imageData[position + 1] << 8));

            char a = ((newShort & 0xf) >> 0);
            char r = ((newShort & 0xF000) >> 12);
            char g = ((newShort & 0xF00) >> 8);
            char b = ((newShort & 0xf0) >> 4);

            r = (r << 4);
            g = (g << 4);
            b = (b << 4);
            a = (a << 4);

            colorArray[y * stride + x * 4 + 0] = r;
            colorArray[y * stride + x * 4 + 1] = g;
            colorArray[y * stride + x * 4 + 2] = b;
            colorArray[y * stride + x * 4 + 3] = a;
            
            position += 2;
        }
    
        position += pad * 2;
    }
    return colorArray;
}

std::unique_ptr<CImage>& CImageBank::getImg(int i) {
    return images[i];
}

void CImageBank::preload(std::unique_ptr<CRender>& renderer) {
    uint16_t numImages = readShort(*file, offset);
    std::cout << numImages << " images" << std::endl;
    
    
    images.resize(numImages);
    for(int i = 0; i < numImages; i++)
        images[i] = std::make_unique<CImage>();
    
    numBmp = readShort(*file, offset);
    
    handles.resize(numBmp);
    
    for(int i = 0; i < numBmp; i++) {
        offset+=2;

        int mode = readInt(*file, offset);
        int width = readShort(*file, offset);
        int height = readShort(*file, offset);
        
        images[i]->width = width;
        images[i]->height = height;
        
        
        offset+=8;
        
        uint32_t size = readInt(*file, offset);
        
        std::vector<unsigned char> out = decompress(readBytes(*file, offset, size));
        

        // std::ofstream outFile("images/"+std::to_string(i)+".rgba");
        switch(mode) {
            case 0:
                out = AndroidMode0ToRGBA(out, width, height, false);
                break;
            case 1:
                out = AndroidMode1ToRGBA(out, width, height, false);
                break;
            case 3:
                out = AndroidMode3ToRGBA(out, width, height, false);
                break;
            case 4:
                out = AndroidMode4ToRGBA(out, width, height, false);
                break;
            default:
                std::cerr << "Invalid mode " << mode << std::endl;
                break;
        }
        
        // for (const auto &e : out) outFile << e;
        // std::cout << width << " " << i << " " << mode << " " << height << std::endl;
        images[i]->data = renderer->loadImage(width, height, &out.front());
        handles[i] = i;
    }
}
