#include    "BomberIA.h"

using namespace IndieGame;

BomberIA::BomberIA(const std::string &name, Ogre::Entity *ent,
           Ogre::SceneNode *node, const OIS::KeyCode default_dir)
  : Entity(name, ent, node, default_dir)
{

}

BomberIA::~BomberIA() {}

Map::pos BomberIA::whereIsNearestPlayer(Map *map)
{
  Map::pos  togo;
  int       x;
  int       y;
  int       **map_int;
  std::vector<Map::pos> pos_player;

  std::cout << "Début de RUN################" << std::endl;

  togo.x = -1;
  togo.y = -1;

  x = map->getMapPosX(this->getPosition().x);
  y = map->getMapPosY(this->getPosition().z);

  std::cout << "Position de base : " << std::endl;
  std::cout << "x : " << x << std::endl;
  std::cout << "y : " << y << std::endl;
  map_int = map->getMap();

  for (int i = 0; i < map->getHeight(); ++i)
  {
    for (int j = 0; j < map->getWidth(); ++j)
    {
      if (map_int[i][j] == 2 && i != y && j != x)
      {
    togo.y = i;
    togo.x = j;
    pos_player.push_back(togo);
      }
    }
  }
  for (auto it = pos_player.begin(); it < pos_player.end(); ++it)
  {
    std::cout << "Pos player : " << std::endl;
    std::cout << "x = " << (*it).x << std::endl;
    std::cout << "y = " << (*it).y << std::endl;
  }
  std::cout << "Fin de RUN################" << std::endl;
  return (togo);
}

int     BomberIA::run(Map   *map)
{
  Map::pos  pos;

  pos = this->whereIsNearestPlayer(map);
  return (0);
}