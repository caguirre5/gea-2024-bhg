#include "Scene.h"
// #include <print>
#include <iostream>
#include "Entity.h"
#include "Components.h"
#include "Systems.h"

Scene::Scene(const std::string& n, entt::registry& r, SDL_Renderer* renderer)
  : name(n), r(r), renderer(renderer)
{
  // std::print("Scene Initialized: {}\n", n);
  std::cout << "Scene Initialized\n" << std::endl;

}

Scene::~Scene() {
  setupSystems.clear();
  // std::print("Scene Destroyed: {}\n", name);
  std::cout << "Scene Destroyed\n" << std::endl;
}

Entity* Scene::createEntity(const std::string& n) {
  Entity* entity = new Entity(r.create(), this);
  entity->addComponent<NameComponent>(n);
  return entity;
}

Entity* Scene::createEntity(const std::string& n, int x, int y) {
  Entity* entity = new Entity(r.create(), this);
  entity->addComponent<NameComponent>(n);
  entity->addComponent<PositionComponent>(x, y);

  return entity;
}

void Scene::setup() {
  for (auto sys: setupSystems) {
    sys->run();
  }
}

void Scene::update(float dT) {
  for (auto sys: updateSystems) {
    sys->run(dT);
  }
}

void Scene::processEvents(SDL_Event e) {
  for (auto sys: eventSystems) {
    sys->run(e);
  }
}

void Scene::render(SDL_Renderer* render) {
  for (auto sys: renderSystems) {
    sys->run(render);
  }
}