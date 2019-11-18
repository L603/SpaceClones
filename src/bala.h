#ifndef BALAS_H
#define BALAS_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "types.h"
#include "gameObject.h"

class Scene;

class Bala:  public sf::Drawable, public GameObject
{
private:
	hp damage;

public:
	Bala(Scene& _myScene, hp _damage);
	virtual ~Bala();

	void hit(GameObject* target);
};

#endif /* BALAS_H */
