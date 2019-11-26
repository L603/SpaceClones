#include "puntaje.h"

Puntaje::Puntaje(Scene &_myScene, sf::Font &_myFont):
	GameObject(_myScene),
	myFont(_myFont){};

Puntaje::~Puntaje(){};

void Puntaje::setPoints(pointT _points)
{
	points = _points;
}

pointT Puntaje::getPoints()
{
	return points;
}
