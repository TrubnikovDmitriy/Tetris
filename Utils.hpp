#ifndef TETRIS_UTILS_HPP
#define TETRIS_UTILS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <sstream>
#include <fstream>

#define WIDE_BLOCK 25
#define TIC_CLOCK 0.8f
#define TAP_CLOCK 0.1f
#define BACK_VOLUME 5.f
#define FONT_SIZE 20


const std::vector<sf::Color> rand_color {

        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Yellow,
        sf::Color::Cyan,
        sf::Color::Magenta,
        sf::Color::White,
//        sf::Color::Blue
};

struct Press {

        Press(): right(false), down(false), P(false),
                 up(false), space(false), M(false) {}
        bool right;
        bool down;
        bool P;
        bool up;
        bool space;
        bool M;
};

enum class BlockType {

    FREE = 0,
    WALL = 1,
};

class Expection {
    public:
        Expection(std::string str = "file")
                :error("Can't load ") {
            error += str;
        }
        void show_error() {
            std::cout << error << std::endl;
        }

    private:
        std::string error;
};

#endif