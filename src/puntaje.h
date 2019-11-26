#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <SFML/Graphics.hpp>

#include "types.h"
#include "assetCommon.h"
#include "gameObject.h"

class Puntaje: public GameObject, public sf::Drawable
{
private:
	sf::Font &myFont;
	pointT points;

public:
	Puntaje(Scene &_myScene, sf::Font &_myFont);
	virtual ~Puntaje();

	virtual void update();

	void setPoints(pointT _points);
	pointT getPoints();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	static std::weak_ptr<Puntaje> spawn(Scene& _myScene, sf::Vector2f position);
};

#endif /* PUNTAJE_H */
