#include "headers/State.h"
#include "headers/Game.h"

State::State(Game* game)
    :p_game(game)
{
    m_backText = sf::Text("press backspace to return", game->fonts()->get("about_font"), 16);
}
State::~State()
{
    
}