#include "alien.h"

Alien::Alien(Scene& _myScene):GameObject(_myScene),
	RigidBody(25,RigidBody::faction::alien),
	Damageable(1)
	{};

Alien::~Alien(){};

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	// Renderizando un círculo
	sf::CircleShape cir(RigidBody::radius);

	sf::Vector2f pos = GameObject::getPosition();

	cir.setOrigin(cir.getRadius(), cir.getRadius());

	cir.setPosition(pos);

	cir.setFillColor(sf::Color(128, 128, 128));

	target.draw(cir);
}

void Alien::update()
{
	RigidBody::setPosition(GameObject::getPosition());
}

std::weak_ptr<Alien> Alien::spawn(Scene& _myScene, sf::Vector2f position)
{

	// Creo un nuevo alien
	Alien *newAlien = new Alien(_myScene);

	// Añado la nave a la lista de objetos de la escena
	auto smartPtr = newAlien->addToList();

	// Convierto el smart pointer de la clase base a Alien
	auto newPointer = std::dynamic_pointer_cast<Alien>(smartPtr.lock());

	newPointer->GameObject::setPosition(position);

	return newPointer;
}

void Alien::damage(hp _damage)
{
	life -=_damage;
	if(life <= 0)
		despawn();
}
