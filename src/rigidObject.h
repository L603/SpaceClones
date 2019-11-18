#ifndef RIGIDOBJECT_H
#define RIGIDOBJECT_H

#include <SFML/Graphics.hpp>

#include "gameObject.h"
#include "types.h"

class RigidObject: public sf::Transformable
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
	RigidObject(pixel _radius, faction _myFaction);
	virtual ~RigidObject();
};

#endif /* RIGIDOBJECT_H */
