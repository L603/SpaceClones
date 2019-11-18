#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "bala.h"
#include "damageable.h"
#include "gameObject.h"
#include "scene.h"
#include "rigidBody.h"


Bala::Bala(Scene& _myScene,
	sf::Vector2f _velocity,
	hp _damage,
	pixel _radius,
	RigidBody::faction _faction):
		GameObject(_myScene),
		velocity(_velocity),
		damage(_damage),
		radius(_radius),
		RigidBody(_radius, _faction){};


Bala::~Bala(){};


void Bala::update()
{
	RigidBody::setPosition(GameObject::getPosition());
	if(GameObject::getPosition().y < 0)
	{
		despawn();
	}
	GameObject::move(velocity);
}

void Bala::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	// Renderiza un círculo
	sf::CircleShape cir(radius);

	sf::Vector2f pos = GameObject::getPosition();

	cir.setOrigin(cir.getRadius(), cir.getRadius());

	cir.setPosition(pos);

	cir.setFillColor(sf::Color(255, 255, 255));

	target.draw(cir);
}

std::weak_ptr<Bala> Bala::spawn(
	Scene& _myScene,
	sf::Vector2f position,
	sf::Vector2f _velocity,
	hp _damage,
	pixel radius,
	RigidBody::faction _faction)
{

	// Creo una nueva bala
	Bala *newBala = new Bala(_myScene, _velocity, _damage, radius, _faction);

	// Añado la bala a la lista de objetos de la escena
	auto smartPtr = newBala->addToList();

	// Convierto el smart pointer de la clase base a Bala
	auto newPointer = std::dynamic_pointer_cast<Bala>(smartPtr.lock());

	newPointer->GameObject::setPosition(position);
	newPointer->RigidBody::setPosition(position);

	return newPointer;
}

void Bala::onCollision(std::weak_ptr<RigidBody> target)
{
	// TODO
	// Hay que detectar si el objeto colisionado es un alien
	// obtener su puntero y destruirlo.
	// Y al final destruir la bala y eliminarlo de la lista de GameObjects
}
