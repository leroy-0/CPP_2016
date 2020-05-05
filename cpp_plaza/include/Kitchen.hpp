//
// Created by longle-h on 24/04/17.
//

#ifndef PROJECT_KITCHEN_HPP
#define PROJECT_KITCHEN_HPP

#include <zconf.h>

namespace plazza {
  class Kitchen
  {
  private:
      //Thread pool;
      pid_t     _pid;

  public:
      Kitchen(int nbThread, pid_t mypid);
      ~Kitchen();

      void      run();
      pid_t     getPid();
  };

};

#endif //PROJECT_KITCHEN_HPP
