#include "SFML/Graphics.hpp"
#include"bird.h"
#include"pipes.h"
#include<vector>
#include<map>
#include<iostream>
#include<cstdlib>
#include<ctime>
class Game {
private: 
	// variable
	sf::RenderWindow* window; 
	sf::Event event; 
	sf::Texture bgtex; 
	sf::Sprite bgsprite;  
	sf::Text text; 
	sf::Font font; 

	// private function
	void initwindow();
	void inittexture();
	void initvaraible();

	void pollevents();
	std::map<std::string, sf::Texture*> pipemap; 
	bird b;
	std::vector<pipes*>p, p1; 
	int randno, randnoforpipe2, score; 
	bool gameover, is_scored; 
public: 
	Game(); 
	~Game(); 
	// public function
	const bool isGameRunning() const;
	void initpipetexture();
	void movepipe();
	void deletepipe();
	void deleteanotherpipe();
	void birdpipecollison();
	void scoresystem();
	//void gettinscore();
	void movebird();
	void update(); 
	void render(); 
 };