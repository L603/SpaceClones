#ifndef NAVE_H
#define NAVE_H

#include "gameObject.h"

class Nave: public GameObject
{
private:


public:
	Nave(Scene& _myScene);
	virtual ~Nave();
	static std::weak_ptr<Nave> spawn(Scene& _myScene);
};

#endif /* NAVE_H */
