#ifndef LEVER_H
#define LEVER_H

#include "Item.h"

class Lever : public Item {
public:
    std::string textureName = "Lever";

    Lever()=default;
    ~Lever() override =default;

    Lever(const Lever&)=default;

    string toString() override{
        return "Lever";
    };
};
#endif//LEVER_H
