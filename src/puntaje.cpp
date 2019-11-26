#include "puntaje.h"

Puntaje::Puntaje(Scene &_myScene, sf::Font &_myFont):
	GameObject(_myScene),
	myFont(_myFont),
	points(0){};

Puntaje::~Puntaje(){};

void Puntaje::setPoints(pointT _points)
{
	points = _points;
}

pointT Puntaje::getPoints()
{
	return points;
}

void Puntaje::update()
{
}

void Puntaje::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
}

//std::weak_ptr<Puntaje> Puntaje::spawn(Scene& _myScene, sf::Vector2f position)
//{
//
//}
