#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>
#include <iostream>
#include <memory>

#include "bala.h"
#include "damageable.h"
#include "gameObject.h"
#include "scene.h"


Bala::Bala(Scene& _myScene, sf::Vector2f _velocity, hp _damage):
	GameObject(_myScene),
	velocity(_velocity),
	damage(_damage){};


Bala::~Bala(){};


void Bala::update()
{
	// Despawneando si alcanza el borde
	if(getPosition().y < 0)
	{
		despawn();
	}
	move(velocity);
}

void Bala::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	// Renderiza un círculo
	sf::CircleShape cir(10);

	sf::Vector2f pos = getPosition();

	cir.setOrigin(cir.getRadius(), cir.getRadius());

	cir.setPosition(pos);

	cir.setFillColor(sf::Color(255, 255, 255));

	target.draw(cir);
}

void Bala::hit(GameObject *target)
{
	// TODO
	// Hay que detectar si el objeto colisionado es un alien
	// obtener su puntero y destruirlo.
	// Y al final destruir la bala y eliminarlo de la lista de GameObjects
}

std::weak_ptr<Bala> Bala::spawn(Scene& _myScene, sf::Vector2f _velocity, hp _damage)
{
	// Creo una nueva bala
	Bala *newBala = new Bala(_myScene, _velocity, _damage);

	// Añado la bala a la lista de objetos de la escena
	auto smartPtr = newBala->addToList();

	// Convierto el smart pointer de la clase base a Bala
	return std::dynamic_pointer_cast<Bala>(smartPtr.lock());
}

std::weak_ptr<Bala> Bala::spawn(
	Scene& _myScene,
	sf::Vector2f position,
	sf::Vector2f _velocity,
	hp _damage)
{
	auto newPointer = Bala::spawn(_myScene, _velocity, _damage);
	newPointer.lock()->setPosition(position);

	return newPointer;
}
