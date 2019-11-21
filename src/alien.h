#ifndef ALIEN_H
#define ALIEN_H

#include <SFML/Graphics.hpp>

#include "gameObject.h"
#include "rigidBody.h"
#include "damageable.h"

class Alien: public GameObject, public sf::Drawable, public RigidBody, public Damageable
{
private:
	

public:
	Alien(Scene& myScene);
	virtual ~Alien();

	/// Dibuja al en la ventana de la escena.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	// En colisión
	void onCollision(std::weak_ptr<RigidBody> target){};

	/// Esta función es llamada una vez por tick.
	virtual void update();

	/// Spawnea un nueva alien y retorna un puntero
	static std::weak_ptr<Alien> spawn(Scene& _myScene, sf::Vector2f position);

	/// Función llamada cuando el alien es dañado
	virtual void damage(hp _damage);
};

#endif /* ALIEN_H */
