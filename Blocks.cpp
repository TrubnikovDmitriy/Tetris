#include "Blocks.hpp"

sf::Sprite BlockTypes::get_sprite() {

    return sprite;
}

void BlockTypes::set_color(sf::Color col) {

    sprite.setColor(col);
}

Wall::Wall(): BlockTypes() {

    sprite.setTexture(images.walltexture);
    set_color(sf::Color::Yellow);
    type = BlockType::WALL;
}

Free::Free(): BlockTypes() {

    sprite.setTexture(images.backtexture);
    set_color(sf::Color::Yellow);
    type = BlockType::FREE;
}

Dynblock::Dynblock(): BlockTypes() {

    sprite.setTexture(images.blocktexture);
    type = BlockType::WALL;
}

Block::Block(): BlockTypes() {

    sprite.setTexture(images.blocktexture);
    type = BlockType::WALL;
}

Ghost::Ghost(): BlockTypes() {

    sprite.setTexture(images.ghosttexture);
    type = BlockType::FREE;
}


