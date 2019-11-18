#include <cmath>

#include "rigidBody.h"

RigidBody::RigidBody(pixel _radius, faction _myFaction):
	radius(_radius),
	myFaction(_myFaction){};

RigidBody::~RigidBody(){};

RigidBody::faction RigidBody::getFaction()
{
	return myFaction;
}

/// Esta función detecta si dos círculos están en colisión
void RigidBody::checkCollision(std::weak_ptr<RigidBody> target)
{
	auto targetPtr = target.lock();
	sf::Vector2f distanceVec = getPosition() - targetPtr->getPosition();
	auto module = sqrtf(powf(distanceVec.x, 2)+powf(distanceVec.y, 2));

	if((radius+targetPtr->radius) > module)
	{
		onCollision(target);
	}
}
