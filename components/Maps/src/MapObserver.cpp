

#include "../include/MapObserver.h"
#include <format>
using namespace sf;
using namespace std;

void MapObserver::update() {
    draw();
}

void MapObserver::updateMapOnly(RenderTexture *_window) {

    RectangleShape mapBg(Vector2f{static_cast<float>(window_size_x), static_cast<float>(window_size_y)});
    mapBg.setPosition(0, 0);
//    mapBg.setFillColor(Color(30, 31, 34));

    RectangleShape lineHorizontal(Vector2f(window_size_x, 1));// Horizontal lineHorizontal
    RectangleShape lineVertical(Vector2f(1, window_size_y));  // Vertical lineHorizontal
    lineHorizontal.setFillColor(Color::White);


    _window->draw(mapBg);
    drawGridLines(_window, lineHorizontal, lineVertical);
    drawMap(_window);
}

MapObserver::MapObserver(shared_ptr<Map> map, sf::RenderTexture *window) : grid(map), window(window), window_size_x(window->getSize().x), window_size_y(window->getSize().y) {
    grid->attach(this);
    this->SIZE_MULT = (float) window_size_x / grid->getSizeX();
}

MapObserver::~MapObserver() {
    grid->detach(this);
}

void MapObserver::draw() {

//    if (!window->isOpen()) return;
//    window->clear(Color(30, 31, 34));
//    window->clear();
    // draw

    RectangleShape line(Vector2f(window_size_x, 1));  // Horizontal line
    RectangleShape line_v(Vector2f(1, window_size_y));// Vertical line
    line.setFillColor(Color::White);

    drawGridLines(window, line, line_v);
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
void MapObserver::drawBox(RenderWindow *pWindow, const Color color, float x, float y) const {
    float squareX = x * SIZE_MULT + 1;
    float squareY = y * SIZE_MULT + 1;
    RectangleShape rectangle(Vector2f(SIZE_MULT - 1, SIZE_MULT - 1));
    rectangle.setFillColor(color);
    rectangle.setPosition(squareX, squareY);
    pWindow->draw(rectangle);
}

void MapObserver::drawImage(RenderTexture *pWindow, const char *pathToImage, float x, float y) {
    float squareX = x * SIZE_MULT;
    float squareY = y * SIZE_MULT;

    float targetX = SIZE_MULT + 1;
    float targetY = SIZE_MULT + 1;

    Texture texture;
    if (!texture.loadFromFile(pathToImage)) {
        cout << "Image Failed to load" << endl;
        throw std::invalid_argument("No image found");
    }

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
            string path = "../../assets/images/frames/floor_1.png";
            drawImage(window, path.c_str(), x, y);

            if (cell == nullptr) {
                string path = "../../assets/images/frames/floor_1.png";
                drawImage(window, path.c_str(), x, y);
            } else if (dynamic_cast<Wall*>(cell.get())) {
                drawImage(window, "../../assets/images/frames/wall_mid.png", x, y);
            } else if (auto* player = dynamic_cast<Character*>(cell.get())) {
                drawImage(window, "../../assets/images/frames/knight_m_idle_anim_f0.png", x, y);
            } else if (auto* item = dynamic_cast<ItemContainer*>(cell.get())) {
                drawImage(window, "../../assets/images/frames/crate.png", x, y);
            } else {
                cout << "Type id " << typeid(*cell).name() << endl;
                string path = "../../assets/images/frames/floor_1.png";
                drawImage(window, path.c_str(), x, y);
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
