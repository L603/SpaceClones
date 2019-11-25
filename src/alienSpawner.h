#ifndef ALIENSPAWNER_H
#define ALIENSPAWNER_H

#include "gameObject.h"
#include "alien.h"
#include "types.h"

class AlienSpawner: public GameObject
{
private:
	std::vector<std::vector<std::weak_ptr<Alien>>> aliens;

public:
	AlienSpawner(Scene& _myScene);
	virtual ~AlienSpawner();

	void spawnAliens();
	static std::weak_ptr<AlienSpawner> spawn(Scene& _myScene);
};

#endif /* ALIENSPAWNER_H */
