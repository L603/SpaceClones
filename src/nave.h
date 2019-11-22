#ifndef NAVE_H
#define NAVE_H

#include <SFML/Graphics.hpp>

#include "gameObject.h"
#include "types.h"

/// El protagonista de este juego
class Nave: public GameObject, public sf::Drawable
{
private:
	/// Rounds per second
	timeT RPS = 20.f;

	/// Un tanque que se llena con el tiempo pasado y se vacia al disparar.
	timeT timeTank = 0.f;

public:
	Nave(Scene& _myScene);


	virtual ~Nave();

	/// Dibuja a la nave en la ventana de la escena.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	/// Esta función es llamada una vez por tick.
	virtual void update();

	/// Spawnea una nueva nave y retorna un puntero
	static std::weak_ptr<Nave> spawn(Scene& _myScene, sf::Vector2f position);
};

#endif /* NAVE_H */
