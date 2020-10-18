#include <SFML/Graphics.hpp>
#include <iostream>
#include "Classes/bullet.cpp"
#include <tuple>
#include <string>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#define PI 3.14159265358979323846

int difficulty = 1;
int rand();
double anglePos = 0;
const int numAliens = 6;
const int numAliens1 = 8;
const int numAliens2 = 10;
int r = 600;
int score_count = 0;
class alien {
public:
	sf::Sprite sprite;
	sf::Rect<float> alien_size;
	double alienAnglePos;
	bool alive;
	int r;
	alien(double angle, bool Alive, int rIn, sf::Texture texture);
	alien();
};
alien::alien() {
	alive = true;
	alienAnglePos = 1;
	alien_size = sprite.getGlobalBounds();
	sprite.setOrigin(sf::Vector2f(alien_size.width / 2, alien_size.height / 2));
}
alien::alien(double angle, bool Alive, int rIn, sf::Texture texture) {
	alienAnglePos = angle;
	alive = Alive;
	r = rIn;
	sprite.setTexture(texture);
	alien_size = sprite.getGlobalBounds();
	sprite.setOrigin(sf::Vector2f(alien_size.width / 2, alien_size.height / 2));
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "320 Project");
	window.setFramerateLimit(60);
	printf("Window created and activated \n");

	unsigned int control_motion = 0;
	bool alienHit = false;
	int gradeNum[] = { 0, 1, 2, 3, 4 };
	char gradeLetter[] = { 'F', 'D', 'C', 'B', 'A' };
	int grade = 1;


	// Load font
	sf::Font font;
	if (!font.loadFromFile("Images/bender.otf"))
	{
		std::cout << "Font load failed" << std::endl;
	}
	sf::Text lives;
	lives.setFont(font);
	lives.setCharacterSize(124);
	lives.setFillColor(sf::Color::White);
	//lives.setScale(4, 4);
	lives.setPosition(1400, 800);

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(124);
	score.setFillColor(sf::Color::White);
	score.setPosition(100, 800);

	sf::Text press_space;
	press_space.setFont(font);
	press_space.setCharacterSize(200);
	press_space.setFillColor(sf::Color::White);
	press_space.setPosition(300, 0);
	press_space.setString("Face Invaders");

	sf::Text title;
	title.setFont(font);
	title.setCharacterSize(130);
	title.setFillColor(sf::Color::White);
	title.setPosition(300, 800);
	title.setString("Press SPACE to start");

	sf::Text game_over;
	game_over.setFont(font);
	game_over.setCharacterSize(130);
	game_over.setFillColor(sf::Color::White);
	game_over.setPosition(50, 400);
	game_over.setString("Game over :(\nPress Space\nto restart");




	// Load all textures
	sf::Texture ship_texture;
	sf::Texture alien_texture;
	sf::Texture background_texture;
	sf::Texture bullet_texture;
	sf::Texture proface_texture;

	// Load files to texture
	if (!ship_texture.loadFromFile("Images/spaceShip.png"))
	{
		std::cout << "Image load failed" << std::endl;
		system("pause");
	}
	if (!alien_texture.loadFromFile("Images/alien.png"))
	{
		std::cout << "Image load failed" << std::endl;
		system("pause");
	}
	if (!background_texture.loadFromFile("Images/background.jpg"))
	{
		std::cout << "Image load failed" << std::endl;
		system("pause");
	}
	if (!bullet_texture.loadFromFile("Images/bullet.png"))
	{
		std::cout << "Image load failed" << std::endl;
		system("pause");
	}
	if (!proface_texture.loadFromFile("Images/proface.png"))
	{
		std::cout << "Image load failed" << std::endl;
		system("pause");
	}

	// Make sprites from textures
	sf::Sprite ship;
	ship.setTexture(ship_texture);

	sf::Sprite proface;
	proface.setTexture(proface_texture);

	sf::Sprite background;
	background.setTexture(background_texture);

	sf::Sprite bullet;
	bullet.setTexture(bullet_texture);

	// Start aliens
	alien aliens[numAliens];

	for (int i = 0; i < numAliens; i++) {
		aliens[i].r = r;
		aliens[i].alienAnglePos = (2 * PI) / numAliens * i;
		aliens[i].sprite.setTexture(alien_texture);
		aliens[i].alien_size = aliens[i].sprite.getGlobalBounds();
		aliens[i].sprite.setOrigin(sf::Vector2f(aliens[i].alien_size.width / 2, aliens[i].alien_size.height / 2));
		aliens[i].sprite.setPosition(aliens[i].r * std::sin(aliens[i].alienAnglePos) + (1920 / 2), aliens[i].r * std::cos(aliens[i].alienAnglePos) + (1080 / 2));
		aliens[i].sprite.setRotation(-aliens[i].alienAnglePos * 180 / PI + 180);
		aliens[i].sprite.setScale(7, 7);
	}

	r = 600;
	alien aliens1[numAliens1];

	for (int i = 0; i < numAliens1; i++) {
		aliens1[i].r = r;
		aliens1[i].alienAnglePos = (2 * PI) / numAliens1 * i;
		aliens1[i].sprite.setTexture(alien_texture);
		aliens1[i].alien_size = aliens1[i].sprite.getGlobalBounds();
		aliens1[i].sprite.setOrigin(sf::Vector2f(aliens1[i].alien_size.width / 2, aliens1[i].alien_size.height / 2));
		aliens1[i].sprite.setPosition(aliens1[i].r * std::sin(aliens1[i].alienAnglePos) + (1920 / 2), aliens1[i].r * std::cos(aliens1[i].alienAnglePos) + (1080 / 2));
		aliens1[i].sprite.setRotation(-aliens1[i].alienAnglePos * 180 / PI + 180);
		aliens1[i].sprite.setScale(7, 7);
	}

	alien aliens2[numAliens2];

	for (int i = 0; i < numAliens2; i++) {
		aliens2[i].r = r;
		aliens2[i].alienAnglePos = (2 * PI) / numAliens2 * i;
		aliens2[i].sprite.setTexture(alien_texture);
		aliens2[i].alien_size = aliens2[i].sprite.getGlobalBounds();
		aliens2[i].sprite.setOrigin(sf::Vector2f(aliens2[i].alien_size.width / 2, aliens2[i].alien_size.height / 2));
		aliens2[i].sprite.setPosition(aliens2[i].r * std::sin(aliens2[i].alienAnglePos) + (1920 / 2), aliens2[i].r * std::cos(aliens2[i].alienAnglePos) + (1080 / 2));
		aliens2[i].sprite.setRotation(-aliens2[i].alienAnglePos * 180 / PI + 180);
		aliens2[i].sprite.setScale(7, 7);
	}
	// Set origins for sprites
	sf::Rect<float> ship_size = ship.getGlobalBounds();
	ship.setOrigin(sf::Vector2f(ship_size.width / 2, ship_size.height / 2));

	// Set initial positions for sprites	
	ship.setPosition(150 * std::sin(anglePos) + (1920 / 2), 150 * std::cos(anglePos) + (1080 / 2));
	ship.setRotation(-anglePos * 180 / PI + 180);
	sf::Rect<float> proface_size = proface.getGlobalBounds();
	proface.setOrigin(sf::Vector2f(proface_size.width / 2, proface_size.height / 2));
	proface.setPosition(sf::Vector2f(1920 / 2, 1080 / 2));
	background.setPosition(sf::Vector2f(0, 0));
	bullet.setPosition(sf::Vector2f(-10, -10));
	//bullet2.setPosition(sf::Vector2f(-10, -10));

	// Scale initial sprites
	ship.setScale(10, 10);
	proface.setScale(0.4, 0.4);
	background.setScale(1, 1);
	bullet.setScale(2, 2);
	//bullet2.setScale(2, 2);

	Bullet player_bullet;
	player_bullet = Bullet(-10, -10, 0, 0);
	//player_bullet[1] = Bullet(-10, -10, 2, 0);
	int i = 0;



	
	// Move up 200 pizels
	//ship.move(sf::Vector2f(200, 0));

	// Get position
	//sf::Vector2f position = ship.getPosition();
	//position.x;
	//position.y;

	// Rotate to 45 degrees (clockwise)
	//ship.setRotation(45); 
	// This one increases the angle by 10 degrees
	//ship.rotate(10);
	//float rotation = ship.getRotation();

	// Scale
	//ship.setScale(sf::Vector2f(1.0f, 2.0f));
	//ship.setScale(30, 30);
	// to scale based on current scale:
	//ship.scale(2,2)  //make it (60,60) in this case
	std::chrono::high_resolution_clock::time_point t0;
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	double oneSec = 1;
	double lvl1 = 10;
	double lvl2 = 15;
	double lvl3 = 20;
	while (window.isOpen())
	{
		// Check an event and deal with it 
		sf::Event event;
		bool started = false;
		bool gameOver = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { 
			started = true; 
			t0 = std::chrono::high_resolution_clock::now();
			t1 = std::chrono::high_resolution_clock::now();
		}
		while (started)
		{

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					started = false;
					window.close();
					break;

					// Window is resized
				case sf::Event::Resized:
					std::cout << "new width: " << event.size.width << std::endl;
					std::cout << "new height: " << event.size.height << std::endl;

					// key pressed
				case sf::Event::KeyPressed:

					break;

				}

			}
			// update game
			//Spacebar
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				
				std::cout << "Shoot!" << std::endl;
				// Get ship position
				sf::Vector2f position = ship.getPosition();
				float rotation = ship.getRotation();
				player_bullet.setX(position.x);
				player_bullet.setY(position.y);
				player_bullet.setAng(rotation);
				player_bullet.setSpd(7);
			}
			//Right arrow key
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				anglePos -= 0.05;
				ship.setPosition(150 * std::sin(anglePos) + (1920 / 2), 150 * std::cos(anglePos) + (1080 / 2));
				ship.setRotation(-anglePos * 180 / PI + 180);
			}
			//Left arrow key
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				anglePos += 0.05;
				ship.setPosition(150 * std::sin(anglePos) + (1920 / 2), 150 * std::cos(anglePos) + (1080 / 2));
				ship.setRotation(-anglePos * 180 / PI + 180);
			}
			tuple <float, float> bullet_tuple;
			bullet_tuple = player_bullet.bulletMovement();
			bullet.setPosition(get<0>(bullet_tuple), get<1>(bullet_tuple));
			//bullet2.setPosition(player_bullet[1].getX(), player_bullet[1].getY());
			if (difficulty == 1 || difficulty == 2) {
				for (int i = 0; i < numAliens; i++)
				{
					if (aliens[i].sprite.getGlobalBounds().intersects(bullet.getGlobalBounds()))
					{
						std::cout << "Collision" << std::endl;
						aliens[i].r = 800;
						aliens[i].sprite.setPosition(aliens[i].r * std::sin(aliens[i].alienAnglePos) + (1920 / 2), aliens[i].r * std::cos(aliens[i].alienAnglePos) + (1080 / 2));
						aliens[i].sprite.setRotation(-aliens[i].alienAnglePos * 180 / PI + 180);
						//alienHit = true;
						//alien.setPosition((rand() % 1500), (rand() % 400) + 400); // THIS IS BAD
						if (grade < 4) { grade++; }
					}
					if (aliens[i].sprite.getGlobalBounds().intersects(ship.getGlobalBounds()))
					{
						aliens[i].r = 800;
						aliens[i].sprite.setPosition(aliens[i].r * std::sin(aliens[i].alienAnglePos) + (1920 / 2), aliens[i].r * std::cos(aliens[i].alienAnglePos) + (1080 / 2));
						std::cout << "Collision" << std::endl;
						aliens[i].sprite.setRotation(-aliens[i].alienAnglePos * 180 / PI + 180);
						//alien.setPosition((rand() % 1500), (rand() % 400) + 400); // THIS IS BAD
						if (grade > 0) { grade--; }
					}
					if (aliens[i].sprite.getGlobalBounds().intersects(proface.getGlobalBounds()))
					{
						std::cout << "Collision" << std::endl;
						grade = 0;
						gameOver = true;
					}
				}
			}
			else if (difficulty == 3) {
				for (int i = 0; i < numAliens1; i++)
				{
					if (aliens1[i].sprite.getGlobalBounds().intersects(bullet.getGlobalBounds()))
					{
						std::cout << "Collision" << std::endl;
						aliens1[i].r = 800;
						aliens1[i].sprite.setPosition(aliens1[i].r * std::sin(aliens1[i].alienAnglePos) + (1920 / 2), aliens1[i].r * std::cos(aliens1[i].alienAnglePos) + (1080 / 2));
						aliens1[i].sprite.setRotation(-aliens1[i].alienAnglePos * 180 / PI + 180);
						//alienHit = true;
						//alien.setPosition((rand() % 1500), (rand() % 400) + 400); // THIS IS BAD
						if (grade < 4) { grade++; }
					}
					if (aliens1[i].sprite.getGlobalBounds().intersects(ship.getGlobalBounds()))
					{
						aliens1[i].r = 800;
						aliens1[i].sprite.setPosition(aliens1[i].r * std::sin(aliens1[i].alienAnglePos) + (1920 / 2), aliens1[i].r * std::cos(aliens1[i].alienAnglePos) + (1080 / 2));
						std::cout << "Collision" << std::endl;
						aliens1[i].sprite.setRotation(-aliens1[i].alienAnglePos * 180 / PI + 180);
						//alien.setPosition((rand() % 1500), (rand() % 400) + 400); // THIS IS BAD
						if (grade > 0) { grade--; }
					}
					if (aliens1[i].sprite.getGlobalBounds().intersects(proface.getGlobalBounds()))
					{
						std::cout << "Collision" << std::endl;
						grade = 0;
						gameOver = true;
					}
				}
			}
			else if (difficulty == 4) {
				for (int i = 0; i < numAliens2; i++)
				{
					if (aliens2[i].sprite.getGlobalBounds().intersects(bullet.getGlobalBounds()))
					{
						std::cout << "Collision" << std::endl;
						aliens2[i].r = 800;
						aliens2[i].sprite.setPosition(aliens2[i].r * std::sin(aliens2[i].alienAnglePos) + (1920 / 2), aliens2[i].r * std::cos(aliens2[i].alienAnglePos) + (1080 / 2));
						aliens2[i].sprite.setRotation(-aliens2[i].alienAnglePos * 180 / PI + 180);
						//alienHit = true;
						//alien.setPosition((rand() % 1500), (rand() % 400) + 400); // THIS IS BAD
						if (grade < 4) { grade++; }
					}
					if (aliens2[i].sprite.getGlobalBounds().intersects(ship.getGlobalBounds()))
					{
						aliens2[i].r = 800;
						aliens2[i].sprite.setPosition(aliens2[i].r * std::sin(aliens2[i].alienAnglePos) + (1920 / 2), aliens2[i].r * std::cos(aliens2[i].alienAnglePos) + (1080 / 2));
						std::cout << "Collision" << std::endl;
						aliens2[i].sprite.setRotation(-aliens2[i].alienAnglePos * 180 / PI + 180);
						//alien.setPosition((rand() % 1500), (rand() % 400) + 400); // THIS IS BAD
						if (grade > 0) { grade--; }
					}
					if (aliens2[i].sprite.getGlobalBounds().intersects(proface.getGlobalBounds()))
					{
						std::cout << "Collision" << std::endl;
						grade = 0;
						gameOver = true;
					}
				}
			}
			if (grade == 0) { gameOver = true; }
			std::ostringstream oss;
			oss << "Grade: " << gradeLetter[grade];
			std::string gradeStr = oss.str();
			lives.setString(gradeStr);
			t2 = std::chrono::high_resolution_clock::now();
			auto time_span1 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			if (time_span1.count() > oneSec) {
				score_count += (grade * 1 * difficulty);
				t1 = std::chrono::high_resolution_clock::now();
			}
			std::ostringstream osss;
			osss << "Score: " << score_count;
			std::string scoreStr = osss.str();
			score.setString(scoreStr);

			auto time_span0 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t0);
			if (time_span0.count() > lvl1 && time_span0.count() < lvl2) {
				difficulty = 2;
			}
			else if (time_span0.count() > lvl2 && time_span0.count() < lvl3) {
				if (difficulty != 3) {
					difficulty = 3;
					window.clear();
					}
			}

			else if (time_span0.count() > lvl3) {
				if (difficulty != 4) {
					difficulty = 4;
					window.clear();
				}

			}
			cout << difficulty << endl;
			cout << time_span0.count() << endl;
			control_motion++;
			if (control_motion % (30/difficulty) == 0) {
				if (difficulty == 1 || difficulty == 2) {
					for (int i = 0; i < numAliens; i++) {
						aliens[i].r -= ((rand() % 10) * difficulty);
						aliens[i].alienAnglePos += float(((double(rand() % 11) - 5) / 50) * difficulty);
						aliens[i].sprite.setPosition(aliens[i].r * std::sin(aliens[i].alienAnglePos) + (1920 / 2), aliens[i].r * std::cos(aliens[i].alienAnglePos) + (1080 / 2));
						aliens[i].sprite.setRotation(-aliens[i].alienAnglePos * 180 / PI + 180);
					}
				}
				else if (difficulty == 3) {
					for (int i = 0; i < numAliens1; i++) {
						aliens1[i].r -= ((rand() % 10) * difficulty/2);
						aliens1[i].alienAnglePos += float(((double(rand() % 11) - 5) / 50) * difficulty);
						aliens1[i].sprite.setPosition(aliens1[i].r * std::sin(aliens1[i].alienAnglePos) + (1920 / 2), aliens1[i].r * std::cos(aliens1[i].alienAnglePos) + (1080 / 2));
						aliens1[i].sprite.setRotation(-aliens1[i].alienAnglePos * 180 / PI + 180);
					}
				}
				else if (difficulty == 4) {
					for (int i = 0; i < numAliens2; i++) {
						aliens2[i].r -= ((rand() % 10) * difficulty/4);
						aliens2[i].alienAnglePos += float(((double(rand() % 11) - 5) / 50) * difficulty);
						aliens2[i].sprite.setPosition(aliens2[i].r * std::sin(aliens2[i].alienAnglePos) + (1920 / 2), aliens2[i].r * std::cos(aliens2[i].alienAnglePos) + (1080 / 2));
						aliens2[i].sprite.setRotation(-aliens2[i].alienAnglePos * 180 / PI + 180);
					}
				}
				control_motion = 0;
			}
			/*for (int i = 0; i < numAliens; i++)
			{
				sf::Vector2f alien_loc = aliens[i].sprite.getPosition();
				sf::Vector2f prof_loc = proface.getPosition();
				if (alien_loc.x >= prof_loc.x)
				{
					if (alien_loc.y >= prof_loc.y)
					{
						aliens[i].sprite.move(-1, -1);
					}
					else
					{
						aliens[i].sprite.move(-1, 1);
					}
				}
				else
				{
					if (alien_loc.y >= prof_loc.y)
					{
						aliens[i].sprite.move(1, -1);
					}
					else
					{
						aliens[i].sprite.move(1, 1);
					}
				}
			}*/
			// Make a black window
			window.clear(sf::Color::Black);
			window.draw(background);
			if (difficulty == 1 || difficulty == 2) {
				for (int i = 0; i < numAliens; i++)
				{
					window.draw(aliens[i].sprite);
				}
			}
			else if (difficulty == 3) {
				for (int i = 0; i < numAliens1; i++)
				{
					window.draw(aliens1[i].sprite);
				}
			}
			else if (difficulty == 4) {
				for (int i = 0; i < numAliens2; i++)
				{
					window.draw(aliens2[i].sprite);
				}
			}

			// This is where you draw...
			//if (!alienHit)
			//{
			//window.draw(alien);
			//}
			window.draw(bullet);
			window.draw(ship);
			window.draw(proface);
			window.draw(lives);
			window.draw(score);


			// End the current frame
			window.display();

			while (gameOver)
			{
				window.clear(sf::Color::Black);
				window.draw(background);
				/*
				window.draw(title);
				
				*/
				window.draw(press_space);
				window.draw(bullet);
				window.draw(ship);
				window.draw(proface);
				window.draw(lives);
				window.draw(score);
				window.draw(game_over);
				window.display();
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				started = false;
				difficulty = 1;
				score_count = 0;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					gameOver = false;
					grade = 1;
					r = 600;
					for (int i = 0; i < numAliens; i++) {
						aliens[i].r = r;
						aliens[i].alienAnglePos = (2 * PI) / numAliens * i;
						aliens[i].sprite.setPosition(aliens[i].r * std::sin(aliens[i].alienAnglePos) + (1920 / 2), aliens[i].r * std::cos(aliens[i].alienAnglePos) + (1080 / 2));
						aliens[i].sprite.setRotation(-aliens[i].alienAnglePos * 180 / PI + 180);
					}
					for (int i = 0; i < numAliens1; i++) {
						aliens1[i].r = r;
						aliens1[i].alienAnglePos = (2 * PI) / numAliens1 * i;
						aliens1[i].sprite.setPosition(aliens1[i].r * std::sin(aliens1[i].alienAnglePos) + (1920 / 2), aliens1[i].r * std::cos(aliens1[i].alienAnglePos) + (1080 / 2));
						aliens1[i].sprite.setRotation(-aliens1[i].alienAnglePos * 180 / PI + 180);
					}
					for (int i = 0; i < numAliens2; i++) {
						aliens2[i].r = r;
						aliens2[i].alienAnglePos = (2 * PI) / numAliens2 * i;
						aliens2[i].sprite.setPosition(aliens2[i].r * std::sin(aliens2[i].alienAnglePos) + (1920 / 2), aliens2[i].r * std::cos(aliens2[i].alienAnglePos) + (1080 / 2));
						aliens2[i].sprite.setRotation(-aliens2[i].alienAnglePos * 180 / PI + 180);
					}
				}
			}

		}
		// Make a black window
		window.clear(sf::Color::Black);
		window.draw(background);


		// This is where you draw...
		//if (!alienHit)
		//{
		//window.draw(alien);
		//}
		window.draw(bullet);
		window.draw(ship);
		window.draw(proface);
		window.draw(lives);
		window.draw(title);
		window.draw(press_space);


		// End the current frame
		window.display();		

	}

	return 0;
}
