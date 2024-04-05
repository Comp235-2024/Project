

#include "../include/MapObserver.h"

#include "Pillar.h"
#include "SFML/Graphics/Texture.hpp"
#include <cmath>
#include <cstdlib>

#include <format>
#include <memory>
#include <queue>
#include <random>
using namespace sf;
using namespace std;

void MapObserver::update() {
    draw();
}

void MapObserver::updateMapOnly(RenderTexture *_window) {

    RectangleShape mapBg(Vector2f{static_cast<float>(window_size_x), static_cast<float>(window_size_y)});
    mapBg.setPosition(0, 0);

    RectangleShape lineHorizontal(Vector2f(window_size_x, 1));// Horizontal lineHorizontal
    RectangleShape lineVertical(Vector2f(1, window_size_y));  // Vertical lineHorizontal
    lineHorizontal.setFillColor(Color::White);


    _window->draw(mapBg);
    drawGridLines(_window, lineHorizontal, lineVertical);
    drawMap(_window);
}

MapObserver::MapObserver(shared_ptr<Map> map, sf::RenderTexture *window, MainDataRef data) : grid(map), window(window), window_size_x(window->getSize().x), window_size_y(window->getSize().y), _data(data) {
    grid->attach(this);
    this->SIZE_MULT = (float) window_size_x / grid->getSizeX();
    generateFloorTextureHashMap();
}

MapObserver::MapObserver(shared_ptr<Map> sharedPtr, RenderTexture *pTexture) {

    grid->attach(this);
    this->SIZE_MULT = (float) window_size_x / grid->getSizeX();
    generateFloorTextureHashMap();
}

MapObserver::~MapObserver() {
    grid->detach(this);
}

void MapObserver::draw() {

//    if (!window->isOpen()) return;
//    window->clear(Color(30, 31, 34));
//    window->clear();
    // draw

//    RectangleShape line(Vector2f(window_size_x, 1));  // Horizontal line
//    RectangleShape line_v(Vector2f(1, window_size_y));// Vertical line
//    line.setFillColor(Color::White);
//
//    drawGridLines(window, line, line_v);
    drawMap(window);

//    window->display();
}


void MapObserver::drawGridLines(RenderTexture *window, RectangleShape &line, RectangleShape &line_v) const {
    for (int i = 0; i < window_size_y; i += SIZE_MULT) {
        line.setPosition(0, i);
        window->draw(line);
    }
    for (int i = 0; i < window_size_x; i += SIZE_MULT) {
        line_v.setPosition(i, 0);
        window->draw(line_v);
    }

    int posX = 5;
    int posY = 5;

    // TODO remove these two line for accurate map representation
    // drawRedX(window, posX, posY);
    // drawBox(window, Color::Blue, 10, 10);
}
void MapObserver::drawRedX(RenderWindow *window, float posX, float posY) const {
    float squareX = posX * SIZE_MULT;
    float squareY = posY * SIZE_MULT;
    Vertex line1[] = {
            Vertex(Vector2f(squareX, squareY)),
            Vertex(Vector2f(squareX + SIZE_MULT, squareY + SIZE_MULT))};

    Vertex line2[] = {
            Vertex(Vector2f(squareX + SIZE_MULT, squareY)),
            Vertex(Vector2f(squareX, squareY + SIZE_MULT))};

    // Set the color of the lines
    line1[0].color = Color::Red;
    line1[1].color = Color::Red;
    line2[0].color = Color::Red;
    line2[1].color = Color::Red;

    // Draw the lines to form an "X"
    window->draw(line1, 2, Lines);
    window->draw(line2, 2, Lines);
}
RenderTexture *MapObserver::getWindow() {
    return window;
}


void MapObserver::drawImage(RenderTexture *pWindow, const char *imageName, float x, float y) {
    float squareX = x * SIZE_MULT;
    float squareY = y * SIZE_MULT;

    float targetX = SIZE_MULT + 1;
    float targetY = SIZE_MULT + 1;

    Texture texture = _data->assets.GetTexture(imageName);
    if (texture.getSize().x == 0 && texture.getSize().y == 0){
        _data->assets.LoadTexture(imageName, imageName);
        texture = _data->assets.GetTexture(imageName);
    }

    Sprite sprite;
    sprite.setTexture(texture);

    float scaleX = targetX / sprite.getLocalBounds().width;
    float scaleY = targetY / sprite.getLocalBounds().height;


    sprite.setPosition(squareX, squareY);
    sprite.setScale(scaleX, scaleY);

    pWindow->draw(sprite);
}

void MapObserver::drawFloor(RenderTexture *pWindow, float x, float y) {
    float squareX = x * SIZE_MULT;
    float squareY = y * SIZE_MULT;

    float targetX = SIZE_MULT + 1;
    float targetY = SIZE_MULT + 1;

    const Texture& texture = getTextureForCell(x, y);

    Sprite sprite;
    sprite.setTexture(texture);

    float scaleX = targetX / sprite.getLocalBounds().width;
    float scaleY = targetY / sprite.getLocalBounds().height;


    sprite.setPosition(squareX, squareY);
    sprite.setScale(scaleX, scaleY);

    pWindow->draw(sprite);
}

void MapObserver::drawMap(RenderTexture *_window) {
    float y = 0;
    float x = 0;
    for (auto &row: grid->getGrid()) {
        x = 0;
        for (auto &cell: row) {
            drawFloor(_window, x, y);

            if (cell == nullptr) {
//                string path = "../../assets/images/frames/floor_1.png";
//                drawImage(window, path.c_str(), x, y);
            }
            else if (auto* door = dynamic_cast<Door*>(cell.get())) {
                drawImage(window, door->textureName.c_str(), x, y);
            }
            else if (auto* pillar = dynamic_cast<Pillar*>(cell.get())) {
                drawImage(window, pillar->textureName.c_str(), x, y);
            }
            else if (auto* wall = dynamic_cast<Wall*>(cell.get())) {
                drawImage(window, wall->textureName.c_str(), x, y);
            } else if (auto* player = dynamic_cast<Character*>(cell.get())) {
                drawImage(window, player->textureName.c_str(), x, y);
            } else if (auto* item = dynamic_cast<ItemContainer*>(cell.get())) {
                drawImage(window, item->textureName.c_str(), x, y);
            } else {
                cout << "Type id " << typeid(*cell).name() << endl;
            }
            ++x;
        }
        ++y;
    }
}
int MapObserver::getWindowSizeX() const {
    return window_size_x;
}
int MapObserver::getWindowSizeY() const {
    return window_size_y;
}
float MapObserver::getSizeMult() const {
    return SIZE_MULT;
}
void MapObserver::generateFloorTextureHashMap() {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(1, 8);
    int file = dist(rng);
    for (int i = 0; i < grid->getSizeX(); ++i) {
        for (int j = 0; j < grid->getSizeY(); ++j) {
            //randomly assign a texture to each cell
            if (_data) {
                assignTextureToCell(i, j, _data->assets.GetTexture(format("floor_{}", file)));
                file = dist(rng);
            } else {
                Texture texture;
                string pathToImage = "../../assets/images/frames/floor_1.png";
                if (!texture.loadFromFile(pathToImage)) {
                    cout << "Image Failed to load" << endl;
                    throw std::invalid_argument("No image found");
                }
            }
        }
    }

}
void MapObserver::assignTextureToCell(int x, int y, const Texture &tex) {
    textureMap[{x, y}] = tex;
}

const Texture& MapObserver::getTextureForCell(int x, int y) const {
    auto it = textureMap.find({x, y});
    if (it != textureMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("No texture found for cell");

}
void MapObserver::drawCircleAroundPos(Vector2i position, int i, const Color color, RenderTexture *_window) {
    int steps = i;
    vector<Vector2i> directions = {Vector2i{1, 0}, Vector2i{-1, 0}, Vector2i{0, 1}, Vector2i{0, -1}};
    queue<pair<Vector2i, int>> q; // Pair of position and steps taken
    q.emplace(position, 0);

    while (!q.empty()) {
        auto [currentPos, currentSteps] = q.front();
        q.pop();

        if (!grid->isInBounds(currentPos) || currentSteps > steps) continue;

        auto cell = grid->getGrid()[currentPos.y][currentPos.x];
        if (cell.get() == nullptr || dynamic_cast<Character*>(cell.get())) {
            drawBorderAroundCell(currentPos, color, _window);

            if (currentSteps < steps) {
                for (const auto& dir : directions) {
                    Vector2i nextPos = currentPos + dir;
                    q.emplace(nextPos, currentSteps + 1);
                }
            }
        }
    }
}
void MapObserver::drawBorderAroundCell(const Vector2i &position, const Color &color, RenderTexture *_window) const {


    float squareX = position.x * SIZE_MULT;
    float squareY = position.y * SIZE_MULT;

    float targetX = SIZE_MULT + 1;
    float targetY = SIZE_MULT + 1;

    RectangleShape rectangle(Vector2f(SIZE_MULT - 1, SIZE_MULT - 1));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(color);
    rectangle.setPosition(squareX, squareY);


    float scaleX = targetX / rectangle.getLocalBounds().width;
    float scaleY = targetY / rectangle.getLocalBounds().height;

    rectangle.setPosition(squareX, squareY);
    rectangle.setScale(scaleX, scaleY);

    _window->draw(rectangle);
}
