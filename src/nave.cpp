#include "nave.h"

Nave::Nave(Scene& _myScene):GameObject(_myScene){};

Nave::~Nave(){};

void Nave::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
		sf::CircleShape cir(100);

		sf::Vector2f pos = (sf::Vector2f)target.getSize()*0.5f;
		pos -= sf::Vector2f(cir.getRadius(),cir.getRadius());

		cir.setPosition(pos);

		cir.setFillColor(sf::Color(255, 255, 255));

		target.draw(cir);
}

std::weak_ptr<Nave> Nave::spawn(Scene& _myScene)
{
	// Creo una nueva nave
	Nave *newNave = new Nave(_myScene);

	// Añado la nave a la lista de objetos de la escena
	auto smartPtr = newNave->addToList();

	// Convierto el smart pointer de la clase base a Nave
	return std::dynamic_pointer_cast<Nave>(smartPtr.lock());
}
