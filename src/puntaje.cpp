#include <string>

#include "puntaje.h"
#include "scene.h"
#include "types.h"

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
	sf::Text pointsText("Puntos: " + std::to_string(points), myFont);
	pointsText.setCharacterSize(30);

	pointsText.setPosition(getPosition());

	pointsText.setFillColor(sf::Color(255, 255, 255));

	target.draw(pointsText);
}

std::weak_ptr<Puntaje> Puntaje::spawn(Scene& _myScene, sf::Vector2f position)
{
	Puntaje *newPoints = new Puntaje(_myScene, _myScene.getPathGen().getFont());

	// Añado la nave a la lista de objetos de la escena
	auto smartPtr = newPoints->addToList();

	// Convierto el smart pointer de la clase base a Nave
	auto newPointer = std::dynamic_pointer_cast<Puntaje>(smartPtr.lock());

	newPointer->setPosition(position);

	return newPointer;
}

Puntaje& Puntaje::operator+=(const pointT ii)
{
	this->points += ii;
	return *this;
}
