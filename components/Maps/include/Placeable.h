#ifndef PLACEABLE_H
#define PLACEABLE_H

#include <SFML/Graphics.hpp>
#include <string>

class Placeable {
public:
    sf::Sprite item;
    std::string PlaceableName;
    int permittedCount;
    sf::Text countText;
    sf::RectangleShape countBackground;

    Placeable(std::string* name, int permittedCount);
    Placeable(std::string* name, int permittedCount, sf::Texture* texture);
    Placeable()=default;
    virtual ~Placeable()=default;

};
#endif //PLACEABLE_H
