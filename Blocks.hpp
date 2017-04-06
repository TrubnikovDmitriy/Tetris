#ifndef TETRIS_BLOCKS_HPP
#define TETRIS_BLOCKS_HPP

#include "Utils.hpp"
#include "Images.hpp"

class BlockTypes {

    public:
        sf::Sprite get_sprite();
        void set_color(sf::Color col);
        virtual ~BlockTypes() {};

        Images images;
        BlockType type;

    protected:
        sf::Sprite sprite;
};

class Dynblock: public BlockTypes {

public:
    Dynblock();
};
class Wall: public BlockTypes {

    public:
        Wall();
};
class Free: public BlockTypes {

    public:
        Free();
};
class Block: public BlockTypes {

    public:
        Block();
};
class Ghost: public BlockTypes {

    public:
        Ghost();
};

#endif