#include "maps.hpp"

#include <algorithm>
#include <iostream>

#include "assets.hpp"
#include "tmxlite/ImageLayer.hpp"
#include "tmxlite/Layer.hpp"
#include "tmxlite/Map.hpp"
#include "tmxlite/ObjectGroup.hpp"
#include "tmxlite/TileLayer.hpp"

/* ! Ce fichier n'as pas été completement fait par nous, il est fournis pour la lecture des fichiers TMX du logiciel TILED
Il a néanmoins été modifier afin d'être adapté a notre code*/

tile::tile(SDL_Texture* tset, int x, int y, int tx, int ty, int w, int h) : sheet(tset), x(x), y(y), tx(tx), ty(ty), width(w), height(h) {}

tmx::Object level::getObjectByName(const std::string& Name) {
  tmx::Map map;
  map.load(tmxFilePath);

  for(const auto& layer : map.getLayers()) {
    if(layer->getType() == tmx::Layer::Type::Object) {
      const tmx::ObjectGroup* objectGroup = dynamic_cast<const tmx::ObjectGroup*>(layer.get());

      for(const auto& object : objectGroup->getObjects()) {
        if(object.getName() == Name) {
          return object;
        }
      }
    }
  }
  return tmx::Object();
}

tmx::Object level::getObjectByNameAndType(const std::string& Name, const std::string& Type) {
  tmx::Map map;
  map.load(tmxFilePath);

  for(const auto& layer : map.getLayers()) {
    if(layer->getType() == tmx::Layer::Type::Object) {
      const tmx::ObjectGroup* objectGroup = dynamic_cast<const tmx::ObjectGroup*>(layer.get());

      for(const auto& object : objectGroup->getObjects()) {
        if(object.getName() == Name && object.getType() == Type) {
          return object;
        }
      }
    }
  }
  return tmx::Object();
}

std::vector<tmx::Object> level::getObjectsByType(const std::string& Name) {
  std::vector<tmx::Object> objectsFound;

  tmx::Map map;
  map.load(tmxFilePath);

  for(const auto& layer : map.getLayers()) {
    if(layer->getType() == tmx::Layer::Type::Object) {
      const tmx::ObjectGroup* objectGroup = dynamic_cast<const tmx::ObjectGroup*>(layer.get());

      for(const auto& object : objectGroup->getObjects()) {
        if(object.getType() == Name) {
          objectsFound.push_back(object);
        }
      }
    }
  }

  return objectsFound;  // Retournez le vecteur d'objets trouvés
}
std::vector<tmx::Object> level::getObjects() {
  std::vector<tmx::Object> objectsFound;  // Initialisez un vecteur pour stocker les objets trouvés

  // Load the TMX map from the file
  tmx::Map map;
  map.load(tmxFilePath);

  // Iterate through all the layers in the map
  for(const auto& layer : map.getLayers()) {
    // Check if the layer is of type ObjectGroup
    if(layer->getType() == tmx::Layer::Type::Object) {
      const tmx::ObjectGroup* objectGroup = dynamic_cast<const tmx::ObjectGroup*>(layer.get());

      // Iterate through the objects in the ObjectGroup
      for(const auto& object : objectGroup->getObjects()) {
        objectsFound.push_back(object);
      }
    }
  }

  return objectsFound;  // Retournez le vecteur d'objets trouvés
}
void tile::draw(SDL_Renderer* ren, int dx, int dy) {
  if(!ren || !sheet) return;

  SDL_Rect src;
  src.x = tx;
  src.y = ty;
  src.w = width;
  src.h = height;

  SDL_Rect dest;
  dest.x = static_cast<int>(x - dx);
  dest.y = static_cast<int>(y - dy);
  dest.w = src.w;
  dest.h = src.h;

  SDL_RenderCopy(ren, sheet, &src, &dest);
}

level::level(const std::string& name) : name(name), rows(0), cols(0) { background = Sprite(); }

void level::load(const std::string& path, SDL_Renderer* ren) {
  // Load and parse the Tiled map with tmxlite
  tmx::Map tiled_map;
  tmxFilePath = path;
  tiled_map.load(path);

  this->MapWidth = tiled_map.getTileCount().x;
  this->MapHeight = tiled_map.getTileCount().y;

  tmx::ImageLayer imageLayer = tiled_map.getLayers()[0]->getLayerAs<tmx::ImageLayer>();
  std::string imagePath = imageLayer.getImagePath();

  // We need to know the size of the map (in tiles)
  auto map_dimensions = tiled_map.getTileCount();
  rows = map_dimensions.y;
  cols = map_dimensions.x;
  // We also need to know the dimensions of the tiles.
  auto tilesize = tiled_map.getTileSize();
  tile_width = tilesize.x;
  tile_height = tilesize.y;

  background = Sprite(imagePath.substr(5), 0, 0, 512, 512);
  background.loadImage(ren);

  // Load all of the tilesets and store them in a data structure.
  // I chose to store them in a map.
  auto& map_tilesets = tiled_map.getTilesets();
  for(auto& tset : map_tilesets) {
    auto tex = assets::instance().load_texture(tset.getImagePath(), ren);
    tilesets.insert(std::pair<gid, SDL_Texture*>(tset.getFirstGID(), tex));
  }

  // Move SDL_QueryTexture outside the loop
  int ts_width = 0, ts_height = 0;
  if(!map_tilesets.empty()) {
    SDL_QueryTexture(tilesets.begin()->second, NULL, NULL, &ts_width, &ts_height);
  }

  // This is the hard part; iterate through each layer in the map,
  // poke each tile for the information you need, and store it in
  // our tiles data structure.
  //
  // We start at the bottom most layer, and work our way up with this
  // outer for-loop.
  auto& map_layers = tiled_map.getLayers();
  for(auto& layer : map_layers) {
    // We're only looking to render the tiles on the map, so if
    // this layer isn't a tile layer, we'll move on.
    if(layer->getType() != tmx::Layer::Type::Tile) {
      continue;
    }

    auto* tile_layer = dynamic_cast<const tmx::TileLayer*>(layer.get());

    // Grab all of this layer's tiles.
    auto& layer_tiles = tile_layer->getTiles();

    // Remember when we needed the size of the Tiled map? This
    // is where it comes into play. Because we're making a simple
    // 2D game, each tile belongs in an x,y coordinate, so using
    // a loop can help us visit each place if there's a tile there.
    for(auto y = 0; y < rows; ++y) {
      for(auto x = 0; x < cols; ++x) {
        // the `layer_tiles` vector that our `getTiles()` call
        // returned on line 78 isn't a 2D array, but we can
        // convert our x, y coordinates into an index that we
        // can access it at.
        auto tile_index = x + (y * cols);
        // Grab the GID of the tile we're at.
        auto cur_gid = layer_tiles[tile_index].ID;
        // If the GID is 0, that means it's an empty tile,
        // we don't want to waste time on nothing, nor do we
        // want to store an empty tile.
        if(cur_gid == 0) {
          continue;
        }

        // Find the tileset that this tile belongs to. The tileset
        // whose first GID is less-than-or-equal to this GID, is
        // the tileset our GID belongs to. A tileset with a first
        // GID that is greater than this tile means that this tile
        // does not belong to that tileset.
        auto tset_gid = -1;
        for(auto& ts : tilesets) {
          // cast ts.first to unsigned int
          if(static_cast<unsigned int>(ts.first) <= cur_gid) {
            tset_gid = ts.first;

            break;
          }
        }
        // If we didn't find a valid tileset, skip the tile. We can't
        // render it if we don't have a tileset to pull from
        // If we didn't find a valid tileset, skip the tile. We can't
        // render it if we don't have a tileset to pull from.
        if(tset_gid == -1) {
          continue;
        }

        // Normalize the GID.
        cur_gid -= tset_gid;
        // Calculate the area on the tilesheet to draw from.
        auto region_x = (cur_gid % (ts_width / tile_width)) * tile_width;
        auto region_y = (cur_gid / (ts_width / tile_width)) * tile_height;

        // Calculate the world position of our tile. This is easy,
        // because we're using nested for-loop to visit each x,y
        // coordinate.
        auto x_pos = x * tile_width;
        auto y_pos = y * tile_height;

        // Phew, all done.
        tile t(tilesets[tset_gid], x_pos, y_pos, region_x, region_y, tile_width, tile_height);
        tiles.push_back(t);
      }
    }
  }
}

void level::draw(SDL_Renderer* ren, int dx, int dy) {
  // Vérifier si SDL_Renderer* est valide
  if(!ren) {
    std::cerr << "ERROR: SDL_Renderer* invalide dans level::draw()\n";
    return;
  }

  background.DrawRepeat(ren, getMapWidth() / background.getWidth() + 1, getMapHeight() / background.getHeight() + 1, dx, dy);

  for(auto& tile : tiles) {
    // Vérifier si la méthode draw de chaque tuile est valide
    if(tile.sheet) {
      tile.draw(ren, dx, dy);
    } else {
      std::cerr << "ERROR: SDL_Texture* invalide dans level::draw()\n";
    }
  }
}

int level::getMapWidth() { return this->MapWidth * this->tile_width; }
int level::getMapHeight() { return this->MapHeight * this->tile_height; }
