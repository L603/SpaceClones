#ifndef NAVE_H
#define NAVE_H

#include "gameObject.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Nave: public sf::Drawable, public GameObject
{
private:


public:
	Nave(Scene& _myScene);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	virtual ~Nave();
	static std::weak_ptr<Nave> spawn(Scene& _myScene);
};

#endif /* NAVE_H */
