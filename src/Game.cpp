#include "headers/Game.h"

Game::Game()
	:m_gameWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE)
{
	// Ucitavanje ovih aseta prebaciti mozda u funkciju
	m_gameWindow.setFramerateLimit(60);
	m_textures.load("ball", "../assets/images/ball.png");
	m_textures.load("serbia", "../assets/images/serbia.png");
	m_textures.load("spain", "../assets/images/spain.png");
	m_textures.load("russia", "../assets/images/russia.png");
	m_textures.load("germany", "../assets/images/germany.png");
	m_textures.load("france", "../assets/images/france.png");
	m_textures.load("poland", "../assets/images/poland.png");
	m_textures.load("turkey", "../assets/images/turkey.png");
	m_textures.load("field", "../assets/images/field.png");
	m_textures.load("menu", "../assets/images/menu.jpg");
	m_textures.load("goal", "../assets/images/goal.png");
	m_textures.load("goal2", "../assets/images/goal2.png");
	m_textures.load("loading", "../assets/images/loading.png");

	m_fonts.load("menu_font", "../assets/fonts/menu_font.ttf");
	m_fonts.load("menu_font2", "../assets/fonts/menu_font_2.otf");
	m_fonts.load("about_font", "../assets/fonts/about_font.ttf");

	m_sounds.load("whistle", "../assets/sounds/whistle.wav");
	m_sounds.load("collide", "../assets/sounds/collide.wav");
	m_sounds.load("pull", "../assets/sounds/pull.wav");

	m_currState = new MenuState(this);
}
Game::~Game()
{
	delete m_currState;
}
void Game::run(){
	start();
	while (m_gameWindow.isOpen()) {
		proccessEvents();
		checkForUpdate();
		render();
	}
}
void Game::proccessEvents(){
	sf::Event event;
	while (m_gameWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
			exit();
		}
		if (event.type == sf::Event::KeyPressed)
			m_currState->keyboard(event.key.code);
		if (event.type == sf::Event::MouseButtonPressed || 
			event.type == sf::Event::MouseButtonReleased)
			m_currState->mouse(event.mouseButton);
	}
}

void Game::update(){

	m_currState->update();
}

void Game::render(){
	m_gameWindow.clear(sf::Color::Black);
	m_currState->render(m_gameWindow);
	m_gameWindow.display();
}

void Game::start()
{
	m_clock.restart();
}

void Game::checkForUpdate()
{
	if (m_clock.getElapsedTime().asSeconds() >= UPDATE_TIME) {
		update();
		m_clock.restart();
	}
}
const TextureManager* Game::textures() const {
	return &m_textures;
}
const FontManager* Game::fonts() const {
	return &m_fonts;
}
const SoundBufferManager& Game::sounds() const {
	return m_sounds;
}
void Game::changeState(State* state) {
	delete m_currState;
	m_currState = state;
}
void Game::exit() {
	m_gameWindow.close();
}
