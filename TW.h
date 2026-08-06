//
// Created by Aleksey Fetsenets on 08/01/2025.
//

#ifndef TYPEWRITER_TW_H
#define TYPEWRITER_TW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>

class TW {
private:
    float width;
    float height;
    const float page_width = 610;
    const float page_height = 862;
    const float page_offset = 30;
    const float kerning = 13;
    const float interligne = 20;

    const std::string bell_dir = "resources/sound/bell.mp3";
    sf::SoundBuffer sb_bell_Press;
    sf::Sound bell;
    const std::string path = "resources/saved_pages/";

    const std::string keypress_dir = "resources/sound/keypress.mp3";
    sf::SoundBuffer sb_key_Press;
    sf::Sound key_press;

    const std::string returnpress_dir = "resources/sound/return.mp3";
    sf::SoundBuffer sb_return_Press;
    sf::Sound return_press;

    sf::Image icon_image;
    const std::string icon_dir = "resources/textures/icon.png";

    sf::Sprite sound_btn;
    const std::string sound_on_texture_dir = "resources/textures/on.png";
    const std::string sound_mute_texture_dir = "resources/textures/mute.png";
    sf::Texture mute;
    sf::Texture on;
    bool sound_status = true;

    sf::Texture erase_texture;
    sf::Sprite erase_btn;
    const std::string erase_texture_dir = "resources/textures/erase.png";


    sf::Texture save_texture;
    sf::Sprite save_btn;
    const std::string save_texture_dir = "resources/textures/save.png";


    const std::string font_dir = "resources/font/SpecialElite-Regular.ttf";
    const std::string Textures_dir = "resources/textures/TypewriterShadow.png";
    sf::RenderWindow window;
    sf::RectangleShape page;
    sf::Font font;
    sf::Texture twShadow;
    sf::Sprite typeWriterShadow_Sprite;
    std::vector<sf::Text *> textVector;

    void AddSymbol(char &);

    bool check_border_x_left();

    bool check_border_x_right();

    bool check_border_y_up();

    bool check_border_y_down();

    void clean_page();

    void save_page();

    void mute_sound();

    void draw_objects();

    bool mouse_over(sf::Sprite &);

    void copy_text_position(std::vector<sf::Vector2f> &, sf::Vector2f &);

    void generate_time_number(std::string &);

public:
    TW(float, float);

    ~TW();

    void run();
};


#endif //TYPEWRITER_TW_H
