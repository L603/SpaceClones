#include "nave.h"
#include "bala.h"

Nave::Nave(Scene& _myScene):GameObject(_myScene){};

Nave::~Nave(){};

void Nave::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(3,0);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move(-3,0);
	}

	sf::Vector2f vel = sf::Vector2f(0,-5);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		auto i = Bala::spawn(*myScene, getPosition(), vel, 1);
	}
}

void Nave::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
		sf::CircleShape cir(50);

		sf::Vector2f pos = getPosition();

		cir.setOrigin(cir.getRadius(), cir.getRadius());

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

std::weak_ptr<Nave> Nave::spawn(Scene& _myScene, sf::Vector2f position)
{
	auto newPointer = Nave::spawn(_myScene);
	newPointer.lock()->setPosition(position);

	return newPointer;
}
