#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

#include "types.h"

class Damageable
{
protected:
	hp life;

public:
	Damageable(hp _life);
	virtual ~Damageable();

	virtual void damage(hp _damage);
};

#endif /* DAMAGEABLE_H */
