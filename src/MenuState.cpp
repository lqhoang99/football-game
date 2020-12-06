#include "headers/MenuState.h"

MenuState::MenuState(Game* game)
    :State(game)
{
    m_background.setTexture(p_game->textures()->get("menu"));
    m_options.push_back(sf::Text("Start Game", p_game->fonts()->get("menu_font"), 40));
    m_options.push_back(sf::Text("About", p_game->fonts()->get("menu_font"), 40));
    m_options.push_back(sf::Text("Exit", p_game->fonts()->get("menu_font"), 40));

    m_aboutText = sf::Text("This game is made in C++ from scratch, using SFML \n\nlibrary for audio/video/network.\n\n\n\nDEVELOPERS:\n\n\n\n\
- dimaria95\n\n- filozof50\n\n- ivke11080", p_game->fonts()->get("about_font"), 20);
    m_aboutText.setPosition(50, WINDOW_HEIGHT - 350);

    m_backText.setPosition(5, 10);

    m_ball.setTexture(p_game->textures()->get("ball"));
    

    m_options[0].setPosition(50, WINDOW_HEIGHT - 350);
    m_options[1].setPosition(50, m_options[0].getPosition().y + 80);
    m_options[2].setPosition(50, m_options[1].getPosition().y + 80);

    m_selected = 0;

    setBallPosition();

    m_backgroundMusic.openFromFile("../assets/sounds/menu_music.ogg");
    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.setVolume(60);
    m_backgroundMusic.play();
}
MenuState::~MenuState() {

}

void MenuState::update() {

}
void MenuState::render(sf::RenderWindow& window) {
    window.draw(m_background);
    if (!m_about) {
        for (auto it = m_options.cbegin(); it != m_options.cend(); it++) {
            window.draw(*it);
        }
        window.draw(m_ball);
    } else {
        window.draw(m_aboutText);
        window.draw(m_backText);
    }
}
void MenuState::setBallPosition() {
    sf::Vector2f textPosition = m_options[m_selected].getPosition();
    unsigned textWidth = m_options[m_selected].getLocalBounds().width;

    m_ball.setPosition(textPosition.x + textWidth + 30, textPosition.y + m_ball.getGlobalBounds().height/2);
}

void MenuState::keyboard(sf::Keyboard::Key& key) {
    if (key == sf::Keyboard::Key::S || key == sf::Keyboard::Key::Down) {
        m_selected = (m_selected+1) % m_options.size();
        setBallPosition();
    } else if (key == sf::Keyboard::Key::W  || key == sf::Keyboard::Key::Up) {
        m_selected--;
        if (m_selected < 0)
            m_selected = m_options.size()-1;
        setBallPosition();
    } else if (key == sf::Keyboard::Key::Space) {
        if (m_selected == 0) {
            p_game->changeState(new TeamState(p_game));
        } else if (m_selected == 1) {
            m_about = true;
        } else if ((size_t)m_selected == m_options.size()-1) {
            p_game->exit();
        }
    } else if (key == sf::Keyboard::Key::BackSpace) {
        m_about = false; // kada se klikne dugme backspace, izlazi se iz about
    }
}
void MenuState::mouse(sf::Event::MouseButtonEvent& event) {

}
