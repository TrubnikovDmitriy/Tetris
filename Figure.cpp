#include "Figure.hpp"

using namespace std;

Figure::Figure() {

    color = rand_color[std::rand() % rand_color.size()];
    fig.set_color(color);
}

void Figure::update_location(int add_x, int add_y) {

    for (auto& scrap: location) {
        scrap.first += add_x;
        scrap.second += add_y;
    }
}

void Figure::rotate() {

    std::vector<std::pair<int,int>>::iterator Begin = location.begin();
    std::vector<std::pair<int,int>>::iterator It = Begin + 1;
    int dx;
    int dy;

    for (; It != location.end(); ++It) {
        dx = It->first - Begin->first;
        dy = It->second - Begin->second;
        It->second = Begin->second + dx;
        It->first = Begin->first - dy;
    }

}

void Figure::unrotate() {

    std::vector<std::pair<int,int>>::iterator Begin = location.begin();
    std::vector<std::pair<int,int>>::iterator It = Begin + 1;
    int dx;
    int dy;


    for (; It != location.end(); ++It) {
        dx = It->first - Begin->first;
        dy = It->second - Begin->second;
        It->second = Begin->second - dx;
        It->first = Begin->first + dy;
    }

}



FigT::FigT(int width) {

    location.push_back(std::make_pair(width / 2, 0));
    location.push_back(std::make_pair(width / 2, -1));
    location.push_back(std::make_pair(width / 2 - 1, 0));
    location.push_back(std::make_pair(width / 2 + 1, 0));

}

FigI::FigI(int width) {

    location.push_back(make_pair(width / 2, 0));
    location.push_back(make_pair(width / 2 - 1, 0));
    location.push_back(make_pair(width / 2 - 2, 0));
    location.push_back(make_pair(width / 2 + 1, 0));
}

FigS::FigS(int width) {

    location.push_back(make_pair(width / 2, 0));
    location.push_back(make_pair(width / 2 + 1, 0));
    location.push_back(make_pair(width / 2, -1));
    location.push_back(make_pair(width / 2 + 1, 1));
}

FigJ::FigJ(int width) {

    location.push_back(make_pair(width / 2, 0));
    location.push_back(make_pair(width / 2 + 1, 0));
    location.push_back(make_pair(width / 2 - 1, 0));
    location.push_back(make_pair(width / 2 - 1, -1));
}

FigO::FigO(int width) {

    location.push_back(make_pair(width / 2, -1));
    location.push_back(make_pair(width / 2, 0));
    location.push_back(make_pair(width / 2 + 1, -1));
    location.push_back(make_pair(width / 2 + 1, 0));
}

FigL::FigL(int width) {

    location.push_back(make_pair(width / 2, 0));
    location.push_back(make_pair(width / 2 + 1, 0));
    location.push_back(make_pair(width / 2 - 1, 0));
    location.push_back(make_pair(width / 2 + 1, -1));
}

FigZ::FigZ(int width) {

    location.push_back(make_pair(width / 2, 0));
    location.push_back(make_pair(width / 2 - 1, 0));
    location.push_back(make_pair(width / 2, -1));
    location.push_back(make_pair(width / 2 - 1, 1));
}
