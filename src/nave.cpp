#include <memory>

#include "scene.h"
#include "nave.h"
#include "bala.h"

// Mientras nave no tenga rigidBody
#define RADIUS 50

Nave::Nave(Scene& _myScene):
	GameObject(_myScene)
	{};

Nave::~Nave(){};

void Nave::update() //Desplazamiento de la nave
{
	pixel vel = 1000;
	// Moviemiento derecha/izquierda
	sf::Vector2f deltaPos;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		deltaPos = sf::Vector2f(deltaTime()*vel,0);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		deltaPos = sf::Vector2f(deltaTime()*-vel,0);
	}
	if((getPosition()+deltaPos).x < RADIUS || (getPosition()+deltaPos).x > myScene->getWindow().getSize().x-RADIUS )
	{
		// Choca con el borde
	}
	else
	{
		move(deltaPos);
	}

	// Spawneando balas
	sf::Vector2f vel2 = sf::Vector2f(0,-2000);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeTank > (1.f/RPS))
	{
		auto i = Bala::spawn(*myScene, getPosition(), vel2, 1,5, RigidBody::nave);
		timeTank = 0.f;
	}
	timeTank += deltaTime();
}

void Nave::draw(sf::RenderTarget& target, sf::RenderStates states)const //Datos de la nave
{
	// Renderizando un círculo
	sf::CircleShape cir(RADIUS);

	sf::Vector2f pos = getPosition();

	cir.setOrigin(cir.getRadius(), cir.getRadius());

	cir.setPosition(pos);

	cir.setFillColor(sf::Color(110, 110, 166));

	target.draw(cir);
}

std::weak_ptr<Nave> Nave::spawn(Scene& _myScene, sf::Vector2f position)
{

	// Creo una nueva nave
	Nave *newNave = new Nave(_myScene);

	// Añado la nave a la lista de objetos de la escena
	auto smartPtr = newNave->addToList();

	// Convierto el smart pointer de la clase base a Nave
	auto newPointer = std::dynamic_pointer_cast<Nave>(smartPtr.lock());

	newPointer->setPosition(position);

	return newPointer;
}
