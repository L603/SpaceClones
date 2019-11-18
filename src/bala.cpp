#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "bala.h"
#include "damageable.h"
#include "gameObject.h"
#include "scene.h"


Bala::Bala(Scene& _myScene, hp _damage):
	GameObject(_myScene),
	damage(_damage)
{
	// TODO
	// Hay que añadir la nueva bala a la lista de GameObjects de la escena.
}

Bala::~Bala(){};

void Bala::hit(GameObject *target)
{
	// TODO
	// Hay que detectar si el objeto colisionado es un alien
	// obtener su puntero y destruirlo.
	// Y al final destruir la bala y eliminarlo de la lista de GameObjects
}
