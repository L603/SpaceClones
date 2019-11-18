#ifndef NAVE_H
#define NAVE_H

#include "gameObject.h"
#include <SFML/Graphics.hpp>

class Nave: public GameObject, public sf::Drawable
{
private:


public:
	Nave(Scene& _myScene);


	virtual ~Nave();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	virtual void update();

	static std::weak_ptr<Nave> spawn(Scene& _myScene);
	static std::weak_ptr<Nave> spawn(Scene& _myScene, sf::Vector2f position);
};

#endif /* NAVE_H */
