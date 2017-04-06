//
//  Выпускной проект.
//    Игра "Тетрис"
//

#include <iostream>
#include "Utils.hpp"
#include "Field.hpp"

using namespace std;


int main() {

    unsigned int w = 425;
    unsigned int h = 600;

    srand((unsigned int)time(nullptr));
    try {
        Field field(w, h);
        Press press;
        sf::RenderWindow window(sf::VideoMode(w, h), "Tetris", sf::Style::Close);
        sf::Clock tic_clock;
        sf::Clock tap_clock;
        float tic_time;
        float tap_time;


        while (window.isOpen()) {

            sf::Event event;
            tic_time = tic_clock.getElapsedTime().asSeconds();
            tap_time = tap_clock.getElapsedTime().asSeconds();


            field.check_field(window);

            if (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                field.game_over(window);

            if (event.type == sf::Event::KeyReleased) {
                if (press.space) {
                    if (event.key.code == sf::Keyboard::Space) {
                        field.tic(true);
                        field.draw_field(window);
                        press.space = false;
                    }
                }
                if (press.up) {
                    if (event.key.code == sf::Keyboard::Up) {
                        field.rotate();
                        press.up = false;
                    }
                }
                if (press.M) {
                    if (event.key.code == sf::Keyboard::M) {
                        field.mute();
                        press.M = false;
                    }
                }
                if (press.P) {
                    if (event.key.code == sf::Keyboard::P) {
                        field.pause(window);
                        press.P = false;
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                press.M = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                press.P = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                press.up = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                press.down = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                press.space = true;

            if (tap_time > TAP_CLOCK) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    field.update_figure(-1);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    field.update_figure(+1);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    field.tic();
                tap_clock.restart();
            }
            if (tic_time > TIC_CLOCK) {
                field.tic();
                tic_clock.restart();
            }

            field.draw_field(window);
            window.display();
            window.clear();
        }
    }
    catch(std::bad_alloc err) {
        std::cout << "Bad allocate" << std::endl;
        return EXIT_FAILURE;
    }
    catch(Expection expection) {
        expection.show_error();
        return EXIT_FAILURE;
    }
    catch(std::exception exp ) {
        std::ofstream new_file("../records/records.txt");
        new_file << 0;
        new_file.close();
    }
    catch(...) {
        std::cout << "Unexpected error" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}