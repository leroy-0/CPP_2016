#ifndef PROJECT_BOMBERIA_H
#define PROJECT_BOMBERIA_H

#include    "Entity.hpp"

namespace IndieGame
{
  class BomberIA : public IndieGame::Entity
  {
  public:
    BomberIA(const std::string &name, Ogre::Entity * ent, Ogre::SceneNode *node, const OIS::KeyCode default_dir);
    virtual ~BomberIA();

    int     run(Map *map);

  private:
    Map::pos    whereIsNearestPlayer(Map *map);
  };
}

#endif //PROJEC T_BOMBERIA_H