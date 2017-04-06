#ifndef CLION_TETRIS_IMAGES_HPP
#define CLION_TETRIS_IMAGES_HPP

#include "Utils.hpp"

class Images {
public:
    Images() {

        if (!mutetexture.loadFromFile("../image/mute_25x50.png")
        || !ghosttexture.loadFromFile("../image/ghost_25.png")
        || !blocktexture.loadFromFile("../image/BW_block_25.png")
        || !backtexture.loadFromFile("../image/back_ground25.png")
        || !walltexture.loadFromFile("../image/wall_25.png")
        || !secondgroundtexture.loadFromFile("../image/secondground.png"))
            throw Expection("texture");
    }

    sf::Texture mutetexture;
    sf::Texture ghosttexture;
    sf::Texture blocktexture;
    sf::Texture backtexture;
    sf::Texture walltexture;
    sf::Texture secondgroundtexture;

};

#endif
