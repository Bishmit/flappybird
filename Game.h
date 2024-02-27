#include "SFML/Graphics.hpp"
#include"bird.h"
#include"pipes.h"
#include"ground.h"
#include<memory>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
class Game {
private: 
	// variable
	sf::Event event; 
	sf::Texture bgtex; 
	sf::Sprite bgsprite;  
	sf::Text text; // this is text for the score
	sf::Font font; // this is the font for the score
	sf::Text Highscoretext; // this is text for the highscore
	sf::Font Highscorefont; // this is the font for the highscore
	sf::Text newhighscoremsgtext; 
	sf::Font newhighscoremsgfont; 
	sf::Texture tex; // this is the texture of the gameover png 
	sf::Sprite sprite;// this is the sprite of the gameover png

	// for audio
	sf::SoundBuffer hitbuffer; 
	sf::Sound hitsound; 

	sf::SoundBuffer pointbuffer;
	sf::Sound pointsound;


	sf::Texture playagaintexture; 
	sf::Sprite playagainsprite; 
	std::unique_ptr<sf::RenderWindow> window; 
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> pipemap; 
	std::vector<std::unique_ptr<pipes>> p; 
	std::vector<std::unique_ptr<pipes>> p1;
	std::vector<std::unique_ptr<ground>> groundVector; 

	// private function
	void initwindow();
	void inittexture();
	void initvaraible();
	void initsound();
	void initHighScore();
	void showHighScore();

	void HighScoreMsg();

	void pollevents();
	bird b; 
	int randno, randnoforpipe2, score, highscore; 
	bool gameover, is_scored; 
public: 
	Game(); 
	// public function
	const bool isGameRunning() const;
	void initpipetexture();
	void spawnandmovepipe();
	void spawnandmoveground();
	void deleteground();
	void deletepipe();
	void birdpipecollison();
	void scoresystem();
	void makegroundcollision();
	void GameOverScreen();
	void playagainscreen();
	void restartGame();
	
	void update(); 
	void render(); 
 };