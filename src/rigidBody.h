#ifndef RIGIDOBJECT_H
#define RIGIDOBJECT_H

#include <SFML/Graphics.hpp>

#include "gameObject.h"
#include "types.h"

/// Esta clase guarda los datos para la detección de colisiones
class RigidBody: public sf::Transformable
{
public:
	enum faction
	{
		alien,
		nave,
		escudo,
	};

protected:
	/// El radio del círculo colisionable
	pixel radius;
	/// La facción del colisionable
	faction myFaction;

	/// Esta función es llamada si dos rigidBodies chocan
	virtual void onCollision(std::weak_ptr<RigidBody> target)=0;

public:
	RigidBody(pixel _radius, faction _myFaction);

	/// Esta función detecta si dos círculos están en colisión
	virtual void checkCollision(std::weak_ptr<RigidBody> target);
	virtual ~RigidBody();

	faction getFaction();
};

#endif /* RIGIDOBJECT_H */
