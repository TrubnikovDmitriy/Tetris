#include "Field.hpp"

Field::Field(int w, int h):time(0.f), lines(0) {

    if (w < 4 * WIDE_BLOCK || h < 6* WIDE_BLOCK)
        throw Expection("window (too small sizes)");

    width = w / WIDE_BLOCK;
	high = h / WIDE_BLOCK;
	field.resize((size_t)width);
	for (auto &row: field)
		row.resize((size_t)high);

    for (int i = 1; i < width - 1; ++i) {
        for (int j = 0; j < high - 1; ++j)
            field[i][j] = std::make_shared<Free>();
    }
	for (int i = 0; i < width; ++i) {
		field[i][high - 1] = std::make_shared<Wall>();
	}
	for (int j = 0; j < high; ++j) {
		field[0][j] = std::make_shared<Wall>();
		field[width - 1][j] = std::make_shared<Wall>();
	}

    text.setFont(fonts.font1);
    sounds.backsound_1.setLoop(true);
    sounds.backsound_1.play();
    muted = false;

    create_figure();
    clock.restart();
}

void Field::create_figure() {

    std::vector<std::shared_ptr<Figure>> rand_fig = {

            std::make_shared<FigZ>(width),
            std::make_shared<FigI>(width),
            std::make_shared<FigS>(width),
            std::make_shared<FigO>(width),
            std::make_shared<FigT>(width),
            std::make_shared<FigL>(width),
            std::make_shared<FigJ>(width)
    };
    figure = rand_fig[std::rand() % rand_fig.size()];
}

void Field::update_figure(int add_x) {

    for (auto& scrap: figure->location) {
        if (scrap.second >= 0) {
            if ((field[scrap.first + add_x][scrap.second])->type != BlockType::FREE)
                return;
        }
        else
            if ((field[scrap.first + add_x][scrap.second + 2])->type != BlockType::FREE)
                return;
    }
    figure->update_location(add_x, 0);
}

void Field::tic(bool fall) {

	if (fall) {
		std::vector<int> distance;
		int d;
		for (auto& scrap: figure->location) {
            if (scrap.second >= -1) {
                d = 1;
                while (field[scrap.first][scrap.second + d]->type == BlockType::FREE)
                    ++d;
                distance.push_back(d);
            }
		}
		d = *min_element(distance.begin(), distance.end());
		figure->update_location(0, d - 1);
		imprint();
		return;
	}

	for (auto& scrap: figure->location) {
        if (scrap.second >= 0) {
            if (field[scrap.first][scrap.second + 1]->type != BlockType::FREE) {
                imprint();
                return;
            }
        }
	}
	figure->update_location(0, +1);
}

void Field::imprint() {

    sounds.fallsound.play();
	for (auto& scrap: figure->location) {
        if (scrap.second >= 0) {
            field[scrap.first][scrap.second] = std::make_shared<Block>();
            field[scrap.first][scrap.second]->set_color(figure->color);
        }
    }

    for (int i = 1; i < width - 1; ++i)
        if (field[i][1]->type == BlockType::WALL) return;
    create_figure();
}

void Field::rotate() {

    figure->rotate();
    for (auto& scrap: figure->location) {
        if (scrap.second >= 0)
        if (field[scrap.first][scrap.second]->type != BlockType::FREE) {
            figure->unrotate();
            sounds.stopsound.play();
            return;
        }
    }

    sounds.rotatesound.play();
}

void Field::delete_line() {

    int count = 0;
    for (int j = high - 2; j >= 0; --j) {

        count = 0;

        for (int i = 1; i < width - 1; ++i) {
            if (field[i][j]->type != BlockType::FREE)
                ++count;
        }

        if (count == width - 2) {
            sounds.crashsound.play();
            ++lines;
            for (int t = j; t > 0; --t) {
                for (int i = 1; i < width - 1; ++i) {
                    field[i][t] = field[i][t - 1];
                }
            }
            --j;
        }

    }
}

void Field::draw_field(sf::RenderWindow &window) {

    //Field
    sf::Sprite sprite;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < high; ++j) {

            sprite = field[i][j]->get_sprite();
            sprite.setPosition(i * WIDE_BLOCK, j * WIDE_BLOCK);
            window.draw(sprite);
        }
    }

    //Ghost
    std::vector<int> distance;
    int d;
    for (auto& scrap: figure->location) {
        if (scrap.second >= -1) {
            d = 1;
            while (field[scrap.first][scrap.second + d]->type == BlockType::FREE)
                ++d;
            distance.push_back(d);
        }
    }
    d = *min_element(distance.begin(), distance.end()) - 1;
    Ghost ghost;
    sprite = ghost.get_sprite();
    for (auto scrap: figure->location) {
        sprite.setPosition(scrap.first * WIDE_BLOCK, (scrap.second + d) * WIDE_BLOCK);
        window.draw(sprite);
    }

    //Dynamic figure
    sprite = figure->fig.get_sprite();
    for (auto scrap: figure->location) {
        if (scrap.second >= 0) {
            sprite.setPosition(scrap.first * WIDE_BLOCK, scrap.second * WIDE_BLOCK);
            window.draw(sprite);
        }
    }

    //Mute icon
    sf::Sprite mutesprite;
    mutesprite.setTexture(images.mutetexture);
    mutesprite.setPosition((width - 2.3f) * WIDE_BLOCK, 1.3f * WIDE_BLOCK);
    if (muted) {
        mutesprite.setTextureRect(sf::IntRect(0, 0, WIDE_BLOCK, WIDE_BLOCK));
        window.draw(mutesprite);
    }
    else {
        mutesprite.setTextureRect(sf::IntRect(0, WIDE_BLOCK, WIDE_BLOCK, WIDE_BLOCK));
        window.draw(mutesprite);
    }

    print_score(window);
}

void Field::check_field(sf::RenderWindow &window) {

    delete_line();
    for (int i = 1; i < width - 1; ++i)
        if (field[i][1]->type == BlockType::WALL) {
            game_over(window);
            return;
        }
}

void Field::print_score(sf::RenderWindow& window) {

    text.setCharacterSize(FONT_SIZE);
    text.setColor(sf::Color::White);

    text.setString("Lines: " + std::to_string(lines));
    text.setPosition(1.4f * WIDE_BLOCK, 0.f);
    window.draw(text);

    time += clock.restart().asSeconds();
    text.setPosition(1.4f * WIDE_BLOCK, 1.f * WIDE_BLOCK);
    text.setString("Time: " + std::to_string((int)time));
    window.draw(text);

    text.setString("pause - \"p\"");
    text.setPosition((width - 5.1f) * WIDE_BLOCK, 0.f);
    window.draw(text);
}

void Field::mute() {

    if (!muted) {
        sounds.backsound_1.setVolume(0.0f);
        muted = true;
    }
    else {
        sounds.backsound_1.setVolume(BACK_VOLUME);
        muted = false;
    }
}

void Field::pause(sf::RenderWindow &window) {

    bool pause_mute = muted;
    bool press = false;
    draw_field(window);

    text.setCharacterSize(2 * FONT_SIZE);
    text.setString(" GAME PAUSE");
    text.setPosition((width / 2 - 5) * WIDE_BLOCK,
                     (high - 7) / 2 * WIDE_BLOCK);
    window.draw(text);

    text.setCharacterSize(FONT_SIZE);
    text.setPosition((width / 2 - 3) * WIDE_BLOCK,
                     (high - 4) / 2 * WIDE_BLOCK);
    text.setString("  for exit press \"esc\"");
    window.draw(text);

    text.setPosition((width / 2 - 3) * WIDE_BLOCK,
                     (high - 2) / 2 * WIDE_BLOCK);
    text.setString(" for muting press \"m\"");
    window.draw(text);

    text.setPosition((width / 2 - 3) * WIDE_BLOCK,
                     (high) / 2 * WIDE_BLOCK);
    text.setString("for continue press \"p\"");
    window.draw(text);

    window.display();
    if (!pause_mute) mute();
    while (window.isOpen()) {

        sf::Event event;

        if (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            game_over(window);


        if (event.type == sf::Event::KeyReleased) {
            if (press) {
                if (event.key.code == sf::Keyboard::P) {
                    if (!pause_mute) mute();
                    clock.restart();
                    return;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            press = true;

    }
}

void Field::game_over(sf::RenderWindow &window) {

    draw_field(window);
    text.setCharacterSize(2 * FONT_SIZE);
    text.setString("\tGAME OVER!\n \t \t lines:"
                   + std::to_string(lines));
    text.setPosition((width / 2 - 6) * WIDE_BLOCK,
                     (high / 2 - 3) * WIDE_BLOCK);
    window.draw(text);

    std::ifstream records("../records/records.txt");
    records.exceptions(std::ios::failbit | std::ios::badbit);
    int rec;
    records >> rec;
    records.close();

    if (lines > rec) {
        std::ofstream new_records("../records/records.txt");
        new_records << lines;
        new_records.close();
        text.setString("New record!!!");
        text.setPosition((width / 2 - 4) * WIDE_BLOCK,
                         (high / 2) * WIDE_BLOCK);
        window.draw(text);

    }
    window.display();

    sounds.backsound_1.stop();
    sounds.gameover.play();
    while (sounds.gameover.getStatus());
    window.close();
}