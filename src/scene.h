#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include <chrono>

#include "gameObject.h"
#include "rigidBody.h"
#include "types.h"

/// Esta clase se encarga de spawnear, despawnear, actualizar y guardar
/// punteros de los gameObjects.
/// También de detectar las colisiones de los RigiBodies.
class Scene
{
private:
	sf::RenderWindow window;

	/// Aquí es donde se guardan todos los objetos del juego.
	std::vector<std::shared_ptr<GameObject>> objects;

	/// Aquí esta todo lo que hay que renderizar.
	std::vector<std::weak_ptr<sf::Drawable>> renderObjects;

	/// Aquí están los objetos colisionables.
	std::unordered_map<RigidBody::faction,
		std::vector<std::weak_ptr<RigidBody>>> rigidBodies;

	/// Una matriz para activar o desactivar colisiones.
	std::unordered_map<RigidBody::faction,
		std::unordered_map<RigidBody::faction, bool>> collisionMatrix;


	/// Detecta las colisiones
	void physicsUpdate();

	/// Acutualiza a los objetos
	void update();

	/// Renderiza a los objetos
	void render();

	/// Elimina a los objetos despawneados
	void postUpdate();

	/// Tiempo desde el último tick
	timeT deltaTime;

	/// Esto es para que GameObject pueda obtener el deltaTime
	friend timeT GameObject::deltaTime();

public:
	Scene();
	virtual ~Scene();

	/// La ventana del juego
	sf::RenderWindow& getWindow();
	/// Esta función añade los GameObject's a la lista interna de la escena.
	std::weak_ptr<GameObject> addObject(GameObject* newObject);

	void start();
};

#endif /* SCENE_H */
