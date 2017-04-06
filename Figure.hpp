#ifndef TETRIS_FIGURE_HPP
#define TETRIS_FIGURE_HPP

#include "Utils.hpp"
#include "Blocks.hpp"

class Figure {

	public:
        Figure();
        virtual ~Figure() {};
		void update_location(int add_x, int add_y);
		virtual void rotate();
        virtual void unrotate();

		std::vector<std::pair<int,int>> location;
        Dynblock fig;
        sf::Color color;
};

class FigT: public Figure {

    public:
        FigT(int width);
};
class FigI: public Figure {

    public:
        FigI(int width);
};
class FigS: public Figure {

    public:
        FigS(int width);
};
class FigZ: public Figure {

    public:
        FigZ(int width);
};
class FigL: public Figure {

    public:
        FigL(int width);
};
class FigJ: public Figure {

    public:
        FigJ(int width);
};
class FigO: public Figure {

    public:
        FigO(int width);
        void rotate() {};
        void unrotate() {};

};

#endif
