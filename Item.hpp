#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>

enum class ItemColor
{
    RED,
    BLUE,
    YELLOW,
    NONE 
};

inline std::string itemColorToString(ItemColor color)
{
    switch (color) {
        case ItemColor::RED: return "RED";
        case ItemColor::BLUE: return "BLUE";
        case ItemColor::YELLOW: return "YELLO";
        case ItemColor::NONE: return "UnKnown";
    }
    return "UnKnown"; 
}


class Item
{
    public:

        Item(std::string name, ItemColor color, int strength, std::string location);

        std::string getName() const;
        ItemColor getColor() const;
        int getStrength() const;
        std::string getLocation() const;

        void displayInfo() const;

    private:

        std::string Name;      
        ItemColor Color;      
        int Strength;          
        std::string Location;  
};

#endif