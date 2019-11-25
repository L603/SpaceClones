#ifndef ALIENSPAWNER_H
#define ALIENSPAWNER_H

#include "gameObject.h"
#include "alien.h"
#include "types.h"

class AlienSpawner: public GameObject
{
private:
	std::vector<std::vector<std::weak_ptr<Alien>>> aliens;
	pixel alienVel;

	/// Un tanque que se llena con el tiempo pasado y se vacia al
	/// cambiar el sentido de la velocidad de los aliens.
	timeT timeTank = 0.f;

public:
	AlienSpawner(Scene& _myScene);
	virtual ~AlienSpawner();

	void spawnAliens();
	virtual void update();
	static std::weak_ptr<AlienSpawner> spawn(Scene& _myScene);
};

#endif /* ALIENSPAWNER_H */
