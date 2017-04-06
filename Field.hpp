#ifndef TETRIS_FIELD_HPP
#define TETRIS_FIELD_HPP

#include "Figure.hpp"
#include "Utils.hpp"
#include "Blocks.hpp"
#include "Sounds.hpp"
#include "Fonts.hpp"


class Field {

	public:
        Field(int w, int h);
        std::shared_ptr<Figure> figure;
        std::vector<std::vector<std::shared_ptr<BlockTypes>>> field;

		void update_figure(int add_x);
		void tic(bool fall = false);
        void rotate();
		void draw_field(sf::RenderWindow &window);
        void pause(sf::RenderWindow &window);
        void check_field(sf::RenderWindow &window);
        void game_over(sf::RenderWindow &window);
        void mute();


	private:
		int width;
		int high;
        Sounds sounds;
        Images images;
        Fonts fonts;
        sf::Text text;
        sf::Clock clock;
        float time;
        bool muted;
        int lines;

		void imprint();
        void create_figure();
        void delete_line();
        void print_score(sf::RenderWindow& window);

};

#endif