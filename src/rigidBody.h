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
		nave
	};

protected:
	pixel radius;
	faction myFaction;

public:
	RigidBody(pixel _radius, faction _myFaction);
	virtual ~RigidBody();
};

#endif /* RIGIDOBJECT_H */
