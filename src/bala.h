#ifndef BALAS_H
#define BALAS_H

#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>

#include "types.h"
#include "gameObject.h"

class Scene;

class Bala: public GameObject, public sf::Drawable
{
private:
	hp damage;

	sf::Vector2f velocity;

public:
	Bala(Scene& _myScene, sf::Vector2f _velocity, hp _damage);
	virtual ~Bala();

	void hit(GameObject* target);
	hp getVida();

	virtual void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	static std::weak_ptr<Bala> spawn(Scene& _myScene, sf::Vector2f _velocity, hp _damage);
	static std::weak_ptr<Bala> spawn(
		Scene& _myScene,
		sf::Vector2f position,
		sf::Vector2f _velocity,
		hp _damage);
};

#endif /* BALAS_H */
