#include "TextureManager.h"
#include <iostream>
#include <unistd.h>  // Para Linux/macOS
//#include <direct.h>  // Para Windows
#include <limits.h>   // Para usar PATH_MAX

std::map<std::string, Texture*> TextureManager::textures;

Texture* TextureManager::LoadTexture(const std::string& filename, SDL_Renderer* renderer) {
  auto it = textures.find(filename);

  if (it != textures.end()) {
    return it->second;
  }

  Texture* texture = new Texture();
  texture->load(filename, renderer);

  textures[filename] = texture;
  return texture;

}

void TextureManager::UnloadTexture(const std::string& filename) {
  auto it = textures.find(filename);

  if (it != textures.end()) {
    delete it->second;
    textures.erase(it);
  }
}

Texture* TextureManager::GetTexture(const std::string& filename) {
  // Obtén el directorio de trabajo actual
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != nullptr) {
    std::cout << "Directorio de trabajo actual: " << cwd << std::endl;
  } else {
    std::cerr << "Error obteniendo el directorio de trabajo actual" << std::endl;
  }

  // Buscar la textura en el mapa
  auto it = textures.find(filename);
  if (it != textures.end()) {
    std::cout << "Textura encontrada en el mapa: " << filename << std::endl;
    return it->second;
  }

  std::cerr << "Textura no encontrada: " << filename << std::endl;
  return nullptr;
}

