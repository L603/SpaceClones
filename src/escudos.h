//
// Created by gian on 20/11/19.
//

#ifndef CLONE_ESCUDOS_H
#define CLONE_ESCUDOS_H

#include "damageable.h"
#include "gameObject.h"
#include <SFML/Graphics.hpp>

class Escudos: public GameObject, public sf::Drawable{
private:
    hp life;

public:
    explicit Escudos(Scene& _myScene);

    virtual ~Escudos();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

    virtual void update();

    static std::weak_ptr<Escudos> spawn(Scene& _myScene, sf::Vector2f position);








};


#endif //CLONE_ESCUDOS_H
