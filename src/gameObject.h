#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "types.h"

class Scene;

class GameObject : public sf::Transformable
{
protected:
	/// La escena a la que pertenece este objeto
	Scene* myScene;

	GameObject(Scene& _myScene);

	/// El objeto es añadido a la lista de la escena y devuelve
	/// un smart pointer.
	std::weak_ptr<GameObject> addToList();

	/// Esto obtiene el deltaTime de la escena
	timeT deltaTime();

	/// Sin esto deltaTime() no funciona
	friend class Scene;
public:
	/// El objeto será eliminado en el lateUpdate() si este flag
	/// está en true.
	bool isDeletable;

	/// Esta función hace que este objeto sea eliminado en el próximo
	/// lateUpdate().
	void despawn();

	/// Esta función es llamada cada tick.
	virtual void update(){};

	/// Esta función es llamada cada tick despues de update().
	virtual void postUpdate(){};

	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H */
