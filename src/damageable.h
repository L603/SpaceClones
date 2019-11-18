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

	void damage(hp _damage);
};

#endif /* DAMAGEABLE_H */
