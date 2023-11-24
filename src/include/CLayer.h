#ifndef CLAYER_H
#define CLAYER_H

class CLayer {
public:
    CLayer() {};
    ~CLayer() {};
    
    uint32_t dwOptions;
    float xCoef;
    float yCoef;
    uint32_t nBkdLOs;
    uint32_t nFirstLOIndex;
    std::string name;
};
#endif
