#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <SFML/Graphics.hpp>

#include "types.h"
#include "assetCommon.h"
#include "gameObject.h"

class Puntaje: public GameObject
{
private:
	sf::Font &myFont;
	pointT points;

public:
	Puntaje(Scene &_myScene, sf::Font &_myFont);
	virtual ~Puntaje();

	void setPoints(pointT _points);
	pointT getPoints();
};

#endif /* PUNTAJE_H */
