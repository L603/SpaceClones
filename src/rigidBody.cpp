#include "rigidBody.h"

RigidBody::RigidBody(pixel _radius, faction _myFaction):
	radius(_radius),
	myFaction(_myFaction){};

RigidBody::~RigidBody(){};

RigidBody::faction RigidBody::getFaction()
{
	return myFaction;
}
