//
// Created by gian on 20/11/19.
//

#include "escudos.h"

Escudos::Escudos(Scene &_myScene):GameObject(_myScene),
                              RigidBody(10,RigidBody::faction::escudo),
                              Damageable(10)
{};

Escudos::~Escudos(){};



void Escudos::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape cir(RigidBody::radius);

    sf::Vector2f pos = GameObject::getPosition();

    cir.setOrigin(cir.getRadius(), cir.getRadius());

    cir.setPosition(pos);

    cir.setFillColor(sf::Color(128, 128, 128));

    target.draw(cir);
}

void Escudos::update()
{
    RigidBody::setPosition(GameObject::getPosition());
}


std::weak_ptr<Escudos> Escudos::spawn(Scene& _myScene, sf::Vector2f position)
{

    // Creo un nuevo alien
    Escudos *newEscudos = new Escudos(_myScene);

    // Añado la nave a la lista de objetos de la escena
    auto smartPtr = newEscudos->addToList();

    // Convierto el smart pointer de la clase base a Alien
    auto newPointer = std::dynamic_pointer_cast<Escudos>(smartPtr.lock());

    newPointer->GameObject::setPosition(position);

    return newPointer;
}

void Escudos::damage(hp _damage)
{
    life -= _damage;
    if(life <= 0)
        despawn();
}



