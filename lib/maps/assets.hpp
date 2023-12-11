#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <map>
#include <memory>
#include <string>

/**
 * @class assets
 * @brief A class for managing game assets such as textures.
 */
class assets {
 public:
  /**
   * @brief Destructor for the assets class.
   */
  ~assets();

  /**
   * @brief Get the instance of the assets class.
   * @return The instance of the assets class.
   */
  static assets& instance();

  /**
   * @brief Load a texture from a file.
   * @param path The path to the texture file.
   * @param ren The SDL renderer to use.
   * @return The loaded SDL texture.
   */
  SDL_Texture* load_texture(const std::string& path, SDL_Renderer* ren);

 private:
  std::map<std::string, SDL_Texture*> textures; /**< A map of texture paths to SDL textures. */

  /**
   * @brief Private constructor for the assets class.
   */
  assets();
};
