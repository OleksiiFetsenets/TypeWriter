//
// Created by Aleksey Fetsenets on 08/01/2025.
//

#include "TW.h"
#include <filesystem>
#include <iostream>

TW::TW(float w, float h) : width(w), height(h),
                           window(sf::VideoMode(static_cast<unsigned int>(w), static_cast<unsigned int>(h)),
                                  "Typewriter") {
    if (!icon_image.loadFromFile(icon_dir)) {
        throw std::runtime_error("Error load icon");
    }
    window.setIcon(icon_image.getSize().x, icon_image.getSize().y, icon_image.getPixelsPtr());


    if (!on.loadFromFile(sound_on_texture_dir)) {
        throw std::runtime_error("Error sound on icon");
    }


    if (!mute.loadFromFile(sound_mute_texture_dir)) {
        throw std::runtime_error("Error sound mute icon");
    }
    sound_btn.setTexture(on);
    sound_btn.setPosition(0, 0);


    if (!save_texture.loadFromFile(save_texture_dir)) {
        throw std::runtime_error("Error save btn");
    }
    save_btn.setTexture(save_texture);
    save_btn.setPosition(60, 0);


    if (!erase_texture.loadFromFile(erase_texture_dir)) {
        throw std::runtime_error("Error erase btn");
    }
    erase_btn.setTexture(erase_texture);
    erase_btn.setPosition(60 * 2, 0);


    page = sf::RectangleShape(sf::Vector2f(page_width, page_height));
    page.setFillColor(sf::Color{246, 238, 227});
    //page.setPosition(150,250);
    page.setPosition(((width / 2) - page_width + page_offset), (height / 4) - 10);
    if (!font.loadFromFile(font_dir)) {
        throw std::runtime_error("Error load font");
    }


    if (!twShadow.loadFromFile(Textures_dir)) {
        throw std::runtime_error("Error load texture");
    }
    typeWriterShadow_Sprite.setTexture(twShadow);
    typeWriterShadow_Sprite.setOrigin(0, 0);
    typeWriterShadow_Sprite.setScale(0.5, 0.5);
    typeWriterShadow_Sprite.setPosition(79, 5);


    if (!sb_key_Press.loadFromFile(keypress_dir)) {
        throw std::runtime_error("Error load sound key press");
    }
    key_press.setBuffer(sb_key_Press);


    if (!sb_return_Press.loadFromFile(returnpress_dir)) {
        throw std::runtime_error("Error load sound return press");
    }
    return_press.setBuffer(sb_return_Press);


    if (!sb_bell_Press.loadFromFile(bell_dir)) {
        throw std::runtime_error("Error load bell sound press");
    }
    bell.setBuffer(sb_bell_Press);
}

void TW::AddSymbol(char &symbol) {
    if (check_border_x_right()) {
        auto *txt = new sf::Text;
        txt->setFont(font);
        txt->setCharacterSize(20);
        txt->setPosition(page.getPosition().x + ((width / 2) - page_width - page.getPosition().x + page_offset),
                         page.getPosition().y + ((height / 4) + 5 - page.getPosition().y)); // Relative to the page
        txt->setFillColor(sf::Color::Black);
        txt->setString(symbol);

        // Move the page after adding the text

        page.setPosition(page.getPosition().x - kerning, page.getPosition().y);
        for (auto text: textVector) {
            text->setPosition(text->getPosition().x - kerning, text->getPosition().y);
        }
        // Add text to the vector
        textVector.push_back(txt);
    }

}

bool TW::check_border_x_left() {
    if (page.getPosition().x < 700) {
        return true;
    } else {
        if (sound_status) { bell.play(); }
    }
    return false;
}

bool TW::check_border_x_right() {
    if (page.getPosition().x > 115) {
        return true;
    } else {
        if (sound_status) { bell.play(); }
    }
    return false;
}


bool TW::check_border_y_up() {
    if (page.getPosition().y < (height / 4 - 10)) {
        return true;
    }
    return false;
}

bool TW::check_border_y_down() {
    if (page.getPosition().y > -(height / 4 - 10)) {
        return true;
    }
    return false;
}

void TW::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.scancode == sf::Keyboard::Scan::Enter ||
                    event.key.scancode == sf::Keyboard::Scan::Down) {
                    if (check_border_y_down()) {
                        page.setPosition(page.getPosition().x, page.getPosition().y - interligne);
                        if (sound_status) { return_press.play(); }
                        for (auto text: textVector) {
                            text->setPosition(text->getPosition().x, text->getPosition().y - interligne);
                        }
                    }
                }
                if (event.key.scancode == sf::Keyboard::Scan::Up) {
                    if (check_border_y_up()) {
                        if (sound_status) { return_press.play(); }
                        page.setPosition(page.getPosition().x, page.getPosition().y + interligne);
                        for (auto text: textVector) {
                            text->setPosition(text->getPosition().x, text->getPosition().y + interligne);
                        }
                    }
                }

                if (event.key.scancode == sf::Keyboard::Scan::Tab) {
                    float old_x = page.getPosition().x;
                    page.setPosition((width / 2) - page_width + page_offset, page.getPosition().y);
                    for (auto text: textVector) {
                        text->setPosition((width / 2) - page_width + page_offset + text->getPosition().x - old_x,
                                          text->getPosition().y);
                    }
                }
                if (event.key.scancode == sf::Keyboard::Scan::Space ||
                    event.key.scancode == sf::Keyboard::Scan::Right) {
                    if (check_border_x_right()) {
                        page.setPosition(page.getPosition().x - kerning, page.getPosition().y);
                        for (auto text: textVector) {
                            text->setPosition(text->getPosition().x - kerning, text->getPosition().y);
                        }
                    }
                }
                if (event.key.scancode == sf::Keyboard::Scan::Backspace ||
                    event.key.scancode == sf::Keyboard::Scan::Left) {
                    if (check_border_x_left()) {
                        page.setPosition(page.getPosition().x + kerning, page.getPosition().y);
                        for (auto text: textVector) {
                            text->setPosition(text->getPosition().x + kerning, text->getPosition().y);
                        }
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    if (sound_status) { key_press.play(); }
                    char typedChar = static_cast<char>(event.text.unicode);
                    if (typedChar != ' ') { AddSymbol(typedChar); }

                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (mouse_over(erase_btn)) {
                    clean_page();
                }
                if (mouse_over(sound_btn)) {
                    mute_sound();
                }
                if (mouse_over(save_btn)) {
                    save_page();
                }
            }
        }
        draw_objects();
    }
}

bool TW::mouse_over(sf::Sprite &btn) {
    return btn.getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(window).x),
                                          static_cast<float>(sf::Mouse::getPosition(window).y));
}

void TW::clean_page() {
    if (sound_status) {
        return_press.play();
        bell.play();
    }
    page.setPosition(((width / 2) - page_width + page_offset), (height / 4) - 10);
    for (auto *text: textVector) {
        delete text;
    }
    textVector.clear();
}

void TW::mute_sound() {
    sound_status = !sound_status;
    sound_status ? sound_btn.setTexture(on) : sound_btn.setTexture(mute);
}

void TW::save_page() {
    std::filesystem::create_directories(path);
    sf::RenderTexture renderT;
    if (!renderT.create(static_cast<unsigned int>(page_width), static_cast<unsigned int>(page_height))) {
        throw std::runtime_error("Error to create render texture for screenshot");
    }
    sf::View camera_view;
    camera_view.reset(sf::FloatRect(0, 0, page_width, page_height));
    renderT.setView(camera_view);
    sf::Vector2f originalPagePos = page.getPosition();
    page.setPosition(0, 0);
    std::vector<sf::Vector2f> originalTextPositions;
    copy_text_position(originalTextPositions, originalPagePos);
    renderT.clear(page.getFillColor());
    renderT.draw(page);
    for (const auto *text: textVector) {
        renderT.draw(*text);
    }
    renderT.display();

    page.setPosition(originalPagePos);
    for (std::size_t i = 0; i < textVector.size(); ++i) {
        textVector[i]->setPosition(originalTextPositions[i]);
    }
    sf::Image screenshot = renderT.getTexture().copyToImage();
    std::string file_name;
    file_name.append(path);
    generate_time_number(file_name);
    if (screenshot.saveToFile(file_name)) {
        std::cout << "Saved" << std::endl;
    } else {
        std::cerr << "Failed to save screenshot" << std::endl;
    }
}

void TW::generate_time_number(std::string &file_name) {
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    int numbers[] = {localTime->tm_mon, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec};
    for (int number: numbers) {
        file_name.append(std::to_string(number));
    }
    file_name.append(".jpeg");
}

void TW::copy_text_position(std::vector<sf::Vector2f> &originalTextPosition, sf::Vector2f &originalPagePos) {
    for (auto *text: textVector) {
        originalTextPosition.push_back(text->getPosition());
        text->setPosition(text->getPosition() - originalPagePos);
    }
}

void TW::draw_objects() {
    window.clear(sf::Color{50, 50, 50});
    window.draw(page);
    window.draw(typeWriterShadow_Sprite);
    window.draw(sound_btn);
    window.draw(save_btn);
    window.draw(erase_btn);
    for (auto text: textVector) {
        window.draw(*text);
    }
    window.display();
}


TW::~TW() {
    for (auto *txt: textVector) {
        delete txt;
    }
}
