#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

#include "types.h"

class Damageable
{
protected:
	hp life;

public:
	Damageable();
	virtual ~Damageable();
};

#endif /* DAMAGEABLE_H */
