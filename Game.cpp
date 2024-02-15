#include "Game.h"
Game::Game()
{
	initwindow(); 
	inittexture(); 
	initpipetexture(); 
	initvaraible(); 
}

void Game::update()
{
	pollevents();
	b.update();
	b.restrictboundarycollison(window.get()); 
	if (!gameover) {
		movepipe();
		spawnandmovepipe(); 
		for (auto &i : p) {
			i->update();
		}
		for (auto &i : p1) {
			i->update();
		}
		for (auto& i : groundVector) {
			i->update();
		}
		GameOverScreen();
	}
	scoresystem(); 
	birdpipecollison();
	makegroundcollision(); 
	deleteground(); 
	deletepipe();	
}

void Game::render()
{
	this->window->clear();  
	this->window->draw(bgsprite); 

	for (int i = 0; i < p.size(); i++) {
		p[i]->render(window.get()); 
	}
	
	for (int i = 0; i < p1.size(); i++) {
		p1[i]->render(window.get());
	}
	for (int i = 0; i < groundVector.size(); i++) {
		groundVector[i]->render(window.get());
	}
	b.render(this->window.get());
	window->draw(text); 
	if (gameover) {
		static sf::Clock cooldownclock;
		const sf::Time cooldowntime = sf::seconds(0.5);
		if (cooldownclock.getElapsedTime() >= cooldowntime) {
			window->draw(sprite);
			//gameover png will be shown after half of the second
		}
	}
	this->window->display(); 
}

void Game::initwindow()
{
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(288, 512), "Flappy Bird");
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
	pipemap["uppipe"] = std::make_unique< sf::Texture>(); 
	pipemap["uppipe"]->loadFromFile("Assets/pipeup.png");

	pipemap["downpipe"] = std::make_unique<sf::Texture>();
	pipemap["downpipe"]->loadFromFile("Assets/pipedown.png"); 
}

void Game::movepipe() {
	// Creating the pipe dynamically
	static sf::Clock cooldownClock;
	const sf::Time cooldownTime = sf::seconds(1);
	randno = rand() % 130;
	randnoforpipe2 = rand() % 80;
	if (cooldownClock.getElapsedTime() >= cooldownTime) {
		p.push_back(std::make_unique<pipes>(pipemap["downpipe"].get(), 300.f, -256.f + randno, -2.f, 0.f, 1.5f));
		p1.push_back(std::make_unique<pipes>(pipemap["uppipe"].get(), 300.f, 250.f + randnoforpipe2, -2.f, 0.f, 1.5f));
		cooldownClock.restart();
	}
}

void Game::spawnandmovepipe() {
	static sf::Clock cooldownclock; 
	const sf::Time cooldowntime = sf::milliseconds(200); 
	if (cooldownclock.getElapsedTime() >= cooldowntime) {
		groundVector.push_back(std::make_unique<ground>(-1.f, 0.f, 0.f, window->getSize().y - 50.f, 2.f));
		cooldownclock.restart(); 
	}
}

void Game::deleteground() {
	auto it = std::remove_if(groundVector.begin(), groundVector.end(), [&](const std::unique_ptr<ground>& g) {
		return g->getbounds().left < -50.f;
		}); 
	groundVector.erase(it, groundVector.end()); 
}

void Game::deletepipe() {
	// deleting the pipes once it reach out of the window
	auto it = std::remove_if(p.begin(), p.end(), [&](const std::unique_ptr<pipes>& pipe) {
		return pipe->getbounds().left <= -50.f;
		});

	p.erase(it, p.end());

	auto it1 = std::remove_if(p1.begin(), p1.end(), [&](const std::unique_ptr<pipes>& pipe) {
		return pipe->getbounds().left <= -50.f;
		});

	p1.erase(it1, p1.end());
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
		for (auto &i : p) {
			gameover = true; 
			b.is_flying = true; 
			b.iskeypressed = true; 
		}
	}
}

void Game::scoresystem() {
	for (int i = 0; i < p.size(); i++) {
		if (!is_scored) {
			if (b.getbounds().left > p[i]->getbounds().left && b.getpos().x + b.getbounds().width < p[i]->getpos().x + p[i]->getbounds().width) {
				// here we start checking, the bird has now entered the pipe but isn't outside of pipe, when it reach outside the condition breaks
				is_scored = true;
			}
		}
		else {
			if (b.getbounds().left + b.getpos().x > p[i]->getpos().x + p[i]->getbounds().width) {
	       // here upper condition break and now ball escape from pipe and now we have to increase the score 
				score++;
				text.setString("Score: " + std::to_string(this->score));
				text.setPosition(170.f, 5.f);
				is_scored = false; // after increasing we have to make the condition false to prevent further scoring
			}
			
		}
	}
}

void Game::makegroundcollision() {
	for (int i = 0; i < groundVector.size(); i++) {
		if (b.getbounds().intersects(groundVector[i]->getbounds())) {
			b.setposition(10.f, 439.f); 	
			/* 
			-  little trick for this
			-  first i find the position of x and y co-oridinate of the ball when it touches the ground 
			-  by doing std::cout << b.getpos().x <<"  " << b.getpos().y << "\n";
			-  and i set the first value to the x and y co-oridinates so it seems like it stops there hehe 
			*/
		}
	}
}

void Game::GameOverScreen() {
		tex.loadFromFile("Assets/gameover.png");
		sprite.setTexture(tex);
		sprite.setPosition(window->getSize().x / 6.0f, window->getSize().y / 3.0f);
		
}












