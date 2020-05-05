/*
** arcade_libopengl.hpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/lib/opengl/inc/arcade_libopengl.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:52:58 2017 Arthur Klein
** Last update Sat Apr 08 16:52:58 2017 Arthur Klein
*/

#ifndef					PROJECT_ARACADE_LIBOPENGL_HPP
#define					PROJECT_ARACADE_LIBOPENGL_HPP

#include				<IL/il.h>
#include				<GL/glew.h>
#include				<GLFW/glfw3.h>
#include				<glm/glm.hpp>
#include				<GL/glut.h>
#include				<GL/freeglut.h>
#include				<iostream>
#include				<map>
#include				"IGraph.hpp"

namespace				arcade
{
    class				libopengl  : public IGraphics
    {
      int				window;
      int				_width;
      int				_height;
      float				_ratiox;
      float				_ratioy;

      std::map<arcade::TileType, float[3] > spriteMap;

    public:
      void        draw(float x, float y, float width, float height, arcade::TileType);
      int 				initDisplay(int width, int height);
      void 				freeDisplay();
      arcade::CommandType		getEvent();
      void				displayMap(arcade::GetMap *map, int score, int x, int y);
      void				loadAssets(const std::string & gameName);
      int				  menu(arcade::CommandType);
      void				vReshape(int w, int h);
      void				vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);
      void				vBitmapOutput(float x, float y, const char *string, void *font);
      int				calc_frame_rate();
      void				calc_sleep();
      virtual				~libopengl() {};
    public:
      libopengl();
    };
}

#endif //PROJECT_ARCADE_OPENGL_HPP