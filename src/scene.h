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
#include "assetCommon.h"
#include "puntaje.h"
#include "nave.h"
#include "bala.h"

/// Esta clase se encarga de spawnear, despawnear, actualizar y guardar
/// punteros de los gameObjects.
/// También de detectar las colisiones de los RigiBodies.
class Scene
{
private:
	sf::RenderWindow window;

	/// Aquí es donde se guardan todos los objetos del juego.
	/// Tiene un puntero compartido, los punteros debiles se relacionan con este.
	/// Se usan punteros inteligentes cuando dependen de otro puntero, como si fuese un ciclo.
	std::vector<std::shared_ptr<GameObject>> objects;

	/// Aquí esta todo lo que hay que renderizar.
	std::vector<std::weak_ptr<sf::Drawable>> renderObjects;

	/// Aquí están los objetos colisionables.
	std::unordered_map<RigidBody::faction,
		std::vector<std::weak_ptr<RigidBody>>> rigidBodies;

	/// Una matriz para activar o desactivar colisiones. Mapa, el primero el primero y segundo es un tipo de dato, nombre del mapa.
	std::unordered_map<RigidBody::faction,
		std::unordered_map<RigidBody::faction, bool>> collisionMatrix;

	/// Aquí están los datos necesarios para obtener el path de los assets
	AssetCommon pathGen;

	/// Aquí está el puntaje
	std::weak_ptr<Puntaje> thePoints;

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

	/// Esto es para que GameObject pueda obtener el deltaTime(El tiempo entre cada frame de un objeto)
	friend timeT GameObject::deltaTime();
	friend Nave::Nave(Scene& _myScene);

public:
	Scene();
	virtual ~Scene();

	/// La ventana del juego
	sf::RenderWindow& getWindow();

	/// Retorna el hacedor de paths de los assets
	AssetCommon& getPathGen();

	/// Retorna una referencia a los puntos
	std::weak_ptr<Puntaje> getPoints();

	/// Esta función añade los GameObject's a la lista interna de la escena.
	std::weak_ptr<GameObject> addObject(GameObject* newObject);

	void start();
};

#endif /* SCENE_H */
