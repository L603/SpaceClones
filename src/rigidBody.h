#ifndef RIGIDOBJECT_H
#define RIGIDOBJECT_H

#include <SFML/Graphics.hpp>

#include "gameObject.h"
#include "types.h"

class RigidBody: public sf::Transformable
{
public:
	enum faction
	{
		alien,
		nave,
		barrera
	};

protected:
	pixel radius;
	faction myFaction;

	/// Esta función es llamada si dos rigidBodies chocan
	virtual void onCollision(std::weak_ptr<RigidBody> target)=0;

public:
	RigidBody(pixel _radius, faction _myFaction);

	virtual void checkCollision(std::weak_ptr<RigidBody> target);
	virtual ~RigidBody();

	faction getFaction();
};

#endif /* RIGIDOBJECT_H */
