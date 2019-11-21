#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


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
public:
	/// El objeto será eliminado en el lateUpdate() si este flag
	/// está en true.
	bool isDeletable;

	/// Esta función hace que este objeto sea eliminado en el próximo
	/// lateUpdate().
	void despawn();

	/// Esta función es llamada cada tick.
	virtual void update()=0;
	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H */
