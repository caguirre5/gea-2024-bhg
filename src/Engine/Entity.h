#pragma once
#include <entt/entt.hpp>
// #include <print>
#include <iostream>
#include <utility>
#include "Scene.h"
#include "Components.h"

class Entity {
public:
  Entity(entt::entity h, Scene* s)
    : handle(h), scene(s)
  {
    // std::print("Entity Created\n");
    std::cout << "Entity Created\n" << std::endl;
  }

  ~Entity() {
    scene->r.destroy(handle);
    // std::print("Enttiy Destroyed\n");
    std::cout << "Entity Destroyed\n" << std::endl;
  }

  template<typename T>
  void addComponent(auto&&... args) {
    scene->r.emplace<T>(handle, std::forward<decltype(args)>(args)...);
  }

private:
  entt::entity handle;
  Scene* scene;
};
