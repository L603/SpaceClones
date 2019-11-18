#include "nave.h"

Nave::Nave(Scene& _myScene):GameObject(_myScene){};

Nave::~Nave(){};

std::weak_ptr<Nave> Nave::spawn(Scene& _myScene)
{
	// Creo una nueva nave
	Nave *newNave = new Nave(_myScene);

	// Añado la nave a la lista de objetos de la escena
	auto smartPtr = newNave->addToList();

	// Convierto el smart pointer de la clase base a Nave
	return std::dynamic_pointer_cast<Nave>(smartPtr.lock());
}
