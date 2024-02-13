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
	if (!gameover) {
		movepipe();
		for (auto* i : p) {
			i->update();
		}
		for (auto* i : p1) {
			i->update();
		}
	}
	scoresystem(); 
	birdpipecollison(); 
	deletepipe(); 
	deleteanotherpipe(); 
}

void Game::render()
{
	this->window->clear();  
	this->window->draw(bgsprite); 

	for (int i = 0; i < p.size(); i++) {
		p[i]->render(window); 
	}
	
	for (int i = 0; i < p1.size(); i++) {
		p1[i]->render(window);
	}
	b.render(this->window);
	window->draw(text); 
	this->window->display(); 
}

void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(288, 512), "Flappy Bird"); 
	window->setFramerateLimit(60); 
}

void Game::inittexture()
{
	if (!bgtex.loadFromFile("Assets/bg.png")) {

	}
	bgsprite.setTexture(bgtex); 

	if (!font.loadFromFile("Fonts/PixellettersFull.ttf")) {
		std::cout << "Error: Font could not be loaded!" << std::endl;
	}
	text.setFont(font); 
	text.setString("Score: " + std::to_string(this->score));
	text.setCharacterSize(34);
	text.setFillColor(sf::Color::White);
	text.setPosition(180.f, 5.f);
}

void Game::initvaraible() {
	this->randno = randno; 
	this->randnoforpipe2 = randnoforpipe2; 
	this->score = 0; 
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
	randno = rand() % 130; 
	randnoforpipe2 = rand() % 80; 
	if (cooldownClock.getElapsedTime() >= cooldownTime) {
		this->p.push_back(new pipes(this->pipemap["downpipe"], 300.f, -256.f + randno ,-2.f, 0.f, 1.5f));
		this->p1.push_back(new pipes(this->pipemap["uppipe"], 300.f, 250.f + randnoforpipe2 , -2.f, 0.f, 1.5f));
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

void Game::birdpipecollison() {
	bool collisionDetected = false;

	
	for (int i = 0; i < p.size(); i++) {
		if (p[i]->getbounds().intersects(b.getbounds())) {
			collisionDetected = true;
			break; 
		}
	}

	
	if (!collisionDetected) {
		for (int i = 0; i < p1.size(); i++) {
			if (p1[i]->getbounds().intersects(b.getbounds())) {
				collisionDetected = true;
				break; 
			}
		}
	}

	if (collisionDetected) {
		std::cout << "Collision detected!" << std::endl;
		for (auto i : p) {
			gameover = true; 
			b.iskeypressed = true; 
		}
	}
}

void Game::scoresystem() {
	
	for (int i = 0; i < p.size(); i++) {
		if (!is_scored) {
			if (b.getbounds().left > p[i]->getbounds().left + p[i]->getbounds().width ) {
				// for some reason it was increasing with 3 points 
				is_scored = true;
			}
		}
		else {
			score++; 
			text.setString("Score: " + std::to_string(this->score/3));
			// so i divide by 3 and make it increase by 3 point haha this works but this is not good logic 
			text.setPosition(170.f, 5.f);
			is_scored = false;
		}
	}
}










