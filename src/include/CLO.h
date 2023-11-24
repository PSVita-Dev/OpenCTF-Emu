#ifndef CLO_H
#define CLO_H

class CLO {
public:
    CLO() {};
    ~CLO() {};
    
    uint16_t loHandle;
    uint16_t loLayer;
    uint16_t loOiHandle;
    uint16_t loOiParentHandle;
    uint16_t loParentType;
    uint16_t loType;
    
    uint32_t loX;
    uint32_t loY;
};
#endif
