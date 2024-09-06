#include "Engine/Game.h"
#include "Engine/Scene.h"
#include "Engine/Entity.h"
#include "Engine/Components.h"
#include "Engine/Systems.h"
#include <SDL_events.h>
#include <SDL_timer.h>
// #include <print>
#include <entt/entt.hpp>
#include "Sprites.h"
#include "Backgrounds.h"

struct PlayerComponent {

};

struct EnemyComponent {

};

class SquareSpawnSetupSystem : public SetupSystem {
  void run() {
    Entity* square = scene->createEntity("SQUARE", 10, 10); 
    square->addComponent<PlayerComponent>();
    square->addComponent<VelocityComponent>(300);
    square->addComponent<TextureComponent>("/home/cristian/Documents/gea-2024-bhg/assets/Sprites/alien.png");
    square->addComponent<SpriteComponent>("/home/cristian/Documents/gea-2024-bhg/assets/Sprites/alien.png", 16, 24, 3, 8, 2000);
  }
};

class EnemySpawnSetupSystem : public SetupSystem {
  void run() {
    Entity* square = scene->createEntity("ENEMY", 200, 200); 
    square->addComponent<EnemyComponent>();
    square->addComponent<TextureComponent>("/home/cristian/Documents/Github/gea-2024-bhg/assets/Sprites/obstacle.png");
    square->addComponent<SpriteComponent>("/home/cristian/Documents/Github/gea-2024-bhg/assets/Sprites/obstacle.png", 24, 24, 3, 8, 2000);
  }
};

class MovementSystem : public UpdateSystem {
  void run(float dT) {
    auto view = scene->r.view<PositionComponent, VelocityComponent>();

    for (auto e : view) {
      auto& pos = view.get<PositionComponent>(e);
      auto vel = view.get<VelocityComponent>(e);

      pos.x += vel.x * dT;
      pos.y += vel.y * dT;
    }
  }
};

class MovementInputSystem : public EventSystem {
  void run(SDL_Event event) {
   auto view = scene->r.view<PlayerComponent, VelocityComponent>();
    for (auto e : view) {
      auto& vel = view.get<VelocityComponent>(e);
      
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) {
          vel.x = -vel.speed;
        }
        if (event.key.keysym.sym == SDLK_RIGHT) {
          vel.x = vel.speed;
        }
        if (event.key.keysym.sym == SDLK_UP) {
          vel.y = -vel.speed;
        }
        if (event.key.keysym.sym == SDLK_DOWN) {
          vel.y = vel.speed;
        }
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_LEFT) {
          vel.x = 0;
        }
        if (event.key.keysym.sym == SDLK_RIGHT) {
          vel.x = 0;
        }
        if (event.key.keysym.sym == SDLK_UP) {
          vel.y = 0;
        }
        if (event.key.keysym.sym == SDLK_DOWN) {
          vel.y = 0;
        }
      }
    }
  }
};


class DemoGame : public Game {
public:
  Scene* sampleScene;
  entt::registry r;

public:
  DemoGame()
  : Game("SAMPLE", 1024, 768)
  { }

  void setup() {
    sampleScene = new Scene("SAMPLE SCENE", r, renderer);
    addSetupSystem<SquareSpawnSetupSystem>(sampleScene);
    addSetupSystem<EnemySpawnSetupSystem>(sampleScene);
    
    addSetupSystem<BackgroundSetupSystem>(sampleScene);
    addSetupSystem<TextureSetupSystem>(sampleScene);
    addEventSystem<MovementInputSystem>(sampleScene);
    addUpdateSystem<SpriteMovementSystem>(sampleScene);
    addUpdateSystem<MovementSystem>(sampleScene);
    addUpdateSystem<SpriteAnimationSystem>(sampleScene);

    addRenderSystem<SpriteRenderSystem>(sampleScene);

    setScene(sampleScene);
  }
}; 
