#ifndef BALAS_H
#define BALAS_H

#include <SFML/Graphics.hpp>
#include "types.h"

class Balas: public sf::Transformable, public sf::Drawable
{
private:
	hp damage;

public:
	Balas();
	virtual ~Balas();
};

#endif /* BALAS_H */
