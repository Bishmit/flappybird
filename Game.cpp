#include "Game.h"
Game::Game()
{
	initwindow(); 
	inittexture(); 
	initpipetexture(); 
	initvaraible(); 
}

Game::~Game()
{
	delete this->window; 

	// deleting the texture 
	for (auto& i : pipemap) {
		delete i.second; 
	}
	
	//deleting from vectors
	for (auto* i : p) {
		delete i; 
	}

	//deleting from vectors
	for (auto* i : p1) {
		delete i;
	}
}

void Game::update()
{
	pollevents();
	b.update(); 
	movepipe();
	for (auto* i : p) {
		i->update(); 
	}
	for (auto* i : p1) {
		i->update();
	}
	deletepipe(); 
	deleteanotherpipe(); 
}

void Game::render()
{
	this->window->clear();  
	this->window->draw(bgsprite); 
	for (auto* i : p) {
		i->render(window); 
	}
	for (auto* i : p1) {
		i->render(window);
	}
	b.render(this->window);
	this->window->display(); 
}

void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(288, 512), "Flappy Bird"); 

}

void Game::inittexture()
{
	if (!bgtex.loadFromFile("Assets/bg.png")) {

	}
	bgsprite.setTexture(bgtex); 
}

void Game::initvaraible() {
	this->randno = randno; 
	this->randnoforpipe2 = randnoforpipe2; 
}

void Game::pollevents() {
	while (window->pollEvent(event)) {
		if (event.key.code == sf::Keyboard::Escape) {
			window->close(); 
		}
		if (event.type == sf::Event::Closed) {
			window->close(); 
		}
	 }
}

const bool Game::isGameRunning() const {
	return window->isOpen(); 
}

void Game::initpipetexture() {
	// it will manage the thing 
	pipemap["uppipe"] = new sf::Texture(); 
	pipemap["uppipe"]->loadFromFile("Assets/pipeup.png");

	pipemap["downpipe"] = new sf::Texture();
	pipemap["downpipe"]->loadFromFile("Assets/pipedown.png"); 
}

void Game::movepipe() {
	// Creating the pipe dynamically
	static sf::Clock cooldownClock;
	const sf::Time cooldownTime = sf::seconds(1);
	randno = rand() % 150; 
	randnoforpipe2 = rand() % 100; 
	if (cooldownClock.getElapsedTime() >= cooldownTime) {
		this->p.push_back(new pipes(this->pipemap["downpipe"], 300.f, -256.f + randno ,-0.12f, 0.f, 0.5f));
		this->p1.push_back(new pipes(this->pipemap["uppipe"], 300.f, 250.f + randnoforpipe2 , -0.12f, 0.f, 0.5f));
		cooldownClock.restart();
	}
}

void Game::deletepipe() {
	// deleting the pipes once it reach out of the window
	int index = 0;
	for (auto* i : p) {
		if (i->getbounds().left <= -50.f) {
			delete this->p[index];
			this->p.erase(this->p.begin() + index);
			std::cout << "shit works" << "\n";
		}
		++index;
		break; 
	}
	
}

void Game::deleteanotherpipe() {
	// deleting the pipes once it reach out of the window
	int index = 0;
	for (auto* i : p1) {
		if (i->getbounds().left <= -50.f) {
			delete this->p1[index];
			this->p1.erase(this->p1.begin() + index);
			std::cout << "shit2 works" << "\n";
		}
		++index;
		break; 
	}
}












