#ifndef CLION_TETRIS_SOUNDS_HPP
#define CLION_TETRIS_SOUNDS_HPP

#include "Utils.hpp"

class Sounds {

    public:
        Sounds() {
            if (!backsound_1.openFromFile("../sound/back_music_1.ogg")
            || !rotatesound.openFromFile("../sound/rotate.wav")
            || !stopsound.openFromFile("../sound/stop.wav")
            || !fallsound.openFromFile("../sound/fall.wav")
            || !gameover.openFromFile("../sound/gameover.wav")
            || !crashsound.openFromFile("../sound/crash.wav"))
                throw Expection("sounds");

            backsound_1.setVolume(BACK_VOLUME);
            crashsound.setVolume(10.f);
            fallsound.setVolume(20.f);
            rotatesound.setVolume(45.f);
            stopsound.setVolume(90.f);
            gameover.setVolume(30.f);
        }

        sf::Music backsound_1;
        sf::Music rotatesound;
        sf::Music stopsound;
        sf::Music crashsound;
        sf::Music fallsound;
        sf::Music gameover;
};

#endif
