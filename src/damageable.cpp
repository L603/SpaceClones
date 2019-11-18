#include "damageable.h"

Damageable::Damageable(hp _life):
	life(_life){};

Damageable::~Damageable(){};

void Damageable::damage(hp _damage){};
