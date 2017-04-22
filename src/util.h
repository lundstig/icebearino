#ifndef UTIL_H_
#define UTIL_H_
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;

void loadTexture(sf::Texture& texture, string file);
void loadSoundBuffer(sf::SoundBuffer& soundBuffer, string file);
void drawSprite(sf::Sprite& sprite, Game* game);
float length(sf::Vector2f v);
float rnd();
float len(V2f v);
V2f norm(V2f v);

#endif
