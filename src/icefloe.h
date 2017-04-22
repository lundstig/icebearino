#ifndef ICEFLOE_H_
#define ICEFLOE_H_
#include <SFML/Graphics.hpp>
#include "polygon.h"

class Game;

struct Part {
public:
	Part();
	float life;
	Polygon polygon;
};

class Icefloe {
public:
	Icefloe();
	vector<Part> parts;
	void update(Game* game);
	void render(Game* game);

};

#endif
