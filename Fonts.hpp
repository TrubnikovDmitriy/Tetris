#ifndef CLION_TETRIS_FONTS_HPP
#define CLION_TETRIS_FONTS_HPP

#include <SFML/Graphics/Font.hpp>
#include <string>

class Fonts {

    public:
        Fonts() {
            if (!font1.loadFromFile("../fonts/old_font.ttf"))
                throw Expection("fonts");
        }
        sf::Font font1;
};

#endif