/*
** arcade_libopengl.cpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/lib/opengl/src/arcade_libopengl.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:53:38 2017 Arthur Klein
** Last update Sat Apr 08 16:53:39 2017 Arthur Klein
*/


#include			<ctime>
#include			<chrono>
#include			<string.h>
#include			<thread>
#include			<sstream>
#include			"arcade_libopengl.hpp"
#include			"Protocol.hpp"

arcade::CommandType		key;

int				arcade::libopengl::calc_frame_rate()
{
  static unsigned int frame_count = 0;
  static int current_fps = 0;
  static double start_time = 0;

  frame_count++;

  double elapsed = (glfwGetTime() - start_time);

  if (elapsed > 1)
  {
    current_fps = frame_count;
    start_time = glfwGetTime();
    frame_count = 0;
  }
  return (current_fps);
}

void				arcade::libopengl::calc_sleep()
{
  static double			target_frame_rate = 60;
  static double			frame_start = 0;
  double			wait_time = 1.0 / (target_frame_rate);
  double			curr_frame_time = glfwGetTime() - frame_start;
  double			dur = 1000.0 * ( wait_time - curr_frame_time ) + 0.5;
  int				durDW = dur;

  if(durDW > 0)
  {
    durDW *= 10;
    std::this_thread::sleep_for(std::chrono::milliseconds(durDW));
  }
  double frame_end = glfwGetTime();
  frame_start = frame_end;
}


arcade::libopengl::libopengl()
{
  this->initDisplay(760, 300);
}

void			keyboard(unsigned char mykey, int x, int y)
{
  static_cast<void>(x);
  static_cast<void>(y);
  if (mykey == 27)
    key = arcade::CommandType::STOP;
  else if (mykey == 233)
    key = arcade::CommandType::SWITCH_LIB_PREV;
  else if (mykey == 34)
    key = arcade::CommandType::SWITCH_LIB_NEXT;
  else if (mykey == 39)
    key = arcade::CommandType::SWITCH_GAME_PREV;
  else if (mykey == 40)
    key = arcade::CommandType::SWITCH_GAME_NEXT;
  else if (mykey == 231)
    key = arcade::CommandType::MENU;
  else if (mykey == 13)
    key = arcade::CommandType::PLAY;
  else if (mykey == 95)
    key = arcade::CommandType::RESTART;
  else
    key = arcade::CommandType::UNDEFINED;
  if (key != arcade::CommandType::PLAY
      && key != arcade::CommandType::SWITCH_GAME_NEXT
      && key != arcade::CommandType::SWITCH_GAME_PREV
      && key != arcade::CommandType::UNDEFINED && key != arcade::CommandType::MENU && key != arcade::CommandType::RESTART)
  {
    glutDestroyWindow(glutGetWindow());
  }
}

void			keyboard_special(int mykey, int x, int y)
{
  static_cast<void>(x);
  static_cast<void>(y);
  if (mykey == GLUT_KEY_LEFT)
    key = arcade::CommandType::GO_LEFT;
  else if (mykey == GLUT_KEY_RIGHT)
    key = arcade::CommandType::GO_RIGHT;
  else if (mykey == GLUT_KEY_DOWN)
    key = arcade::CommandType::GO_DOWN;
  else if (mykey == GLUT_KEY_UP)
    key = arcade::CommandType::GO_UP;
  else
    key = arcade::CommandType::UNDEFINED;
}

void    fake_disp() {};

int			arcade::libopengl::initDisplay(int width, int height)
{
  static bool		first = true;
  char			fakeParam[] = "fake";
  char			*fakeargv[] = { fakeParam, NULL };
  int			fakeargc = 1;

  _width = width;
  _height = height;
  if (first)
    glutInit(&fakeargc, fakeargv);
  first = false;
  glutInitWindowSize(width, height);
  window = glutCreateWindow("OpenGL");
  glutSetWindow(window);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboard_special);
  glutDisplayFunc(fake_disp);
  return (0);
}

void			arcade::libopengl::freeDisplay()
{
  glutMainLoopEvent();
  key = arcade::CommandType::UNDEFINED;
}

void			arcade::libopengl::draw(float x, float y, float width, float height, arcade::TileType tile)
{
  float			r;
  float			g;
  float			b;

  r = this->spriteMap[tile][0];
  g = this->spriteMap[tile][1];
  b = this->spriteMap[tile][2];

  width *= 0.02f;
  height *= 0.02f;
  x *= 0.02f;
  y *= 0.02f;

  x = x - width / 2;
  y = y - height / 2;

  if (y < height / 2)
    y *= -1;
  if (x > width / 2)
    x *= -1;

  x *= _ratiox;
  y *= _ratioy;

  glBegin(GL_QUADS);
  glColor3f(r, g, b);
  glVertex2f((-0.02f * _ratiox) + x, (-0.02f * _ratioy) + y);
  glVertex2f((0.02f * _ratiox) + x, (-0.02f * _ratioy) + y);
  glVertex2f((0.02f * _ratiox) + x,  (0.02f * _ratioy) + y);
  glVertex2f((-0.02f * _ratiox) + x,  (0.02f * _ratioy) + y);
  glEnd();
}

void			arcade::libopengl::displayMap(arcade::GetMap *map, int score, int playerx, int playery)
{
  std::stringstream	trans;

  trans << score << std::endl;
  calc_frame_rate();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glViewport(0, -4, _width, _height);

  for (int i = 0; i < map->height; ++i)
  {
    for (int z = 0; z < map->width ; ++z)
    {
      if (map->tile[i * map->width + z] == arcade::TileType::BLOCK
        && playerx == z && playery == i)
        draw(z, i, map->width, map->height, arcade::TileType::PLAYER);
      else
        draw(z, i, map->width, map->height, map->tile[i * map->width + z]);
    }
  }
  glClearColor(0,0,0,0);
  glColor3d(1,1,1);
  vBitmapOutput(0.6, 0.8,"Score :",GLUT_BITMAP_HELVETICA_18);
  vBitmapOutput(0.9, 0.8,trans.str().c_str(),GLUT_BITMAP_HELVETICA_18);
  glFlush();
  calc_sleep();
}
void arcade::libopengl::vBitmapOutput(float x, float y, const char *string, void *font)
{
  int len,i;

  glRasterPos2f(x,y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) glutBitmapCharacter(font,string[i]);
}

void arcade::libopengl::vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font)
{
  char *p;

  glPushMatrix();
  glTranslatef(x, y, 0);
  for (p = string; *p; p++) glutStrokeCharacter(font, *p);
  glPopMatrix();
}

void arcade::libopengl::vReshape(int w, int h)
{
  float L;
  float H;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w<=h)
  {
    if (w==0) H=800;
    else H=(GLfloat) (400*h/w);
    L=400;
  }
  else
  {
    H=800;
    if (h==0) L=400;
    else L=(GLfloat) (800*w/h);
  }
  gluOrtho2D(-L/2,L/2,-H/2,H/2);
}



int			arcade::libopengl::menu(arcade::CommandType choose)
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1,1,1);
  vBitmapOutput(-0.2, 0.8,"Hey you want a kiss ?!",GLUT_BITMAP_HELVETICA_18);
  if (choose == arcade::CommandType::UNDEFINED)
  {
    vBitmapOutput(-0.2, 0.5,"> Snake",GLUT_BITMAP_HELVETICA_18);
    vBitmapOutput(-0.2, 0.2,"  Pacman",GLUT_BITMAP_HELVETICA_18);
  }
  if (choose == arcade::CommandType::GO_UP)
  {
    vBitmapOutput(-0.2, 0.5,"> Snake",GLUT_BITMAP_HELVETICA_18);
    vBitmapOutput(-0.2, 0.2,"  Pacman",GLUT_BITMAP_HELVETICA_18);
  }
  else if (choose == arcade::CommandType::GO_DOWN)
  {
    vBitmapOutput(-0.2, 0.5,"  Snake",GLUT_BITMAP_HELVETICA_18);
    vBitmapOutput(-0.2, 0.2,"> Pacman",GLUT_BITMAP_HELVETICA_18);
  }
  glFlush();
  return (0);
}

void			arcade::libopengl::loadAssets(const std::string & gameName)
{
 if (gameName.compare("snake") == 0)
  {
    spriteMap[arcade::TileType::BLOCK][0] = 0.0f;
    spriteMap[arcade::TileType::BLOCK][1] = 1.0f;
    spriteMap[arcade::TileType::BLOCK][2] = 0.0f;

    spriteMap[arcade::TileType::POWERUP][0] = 1.0f;
    spriteMap[arcade::TileType::POWERUP][1] = 0.0f;
    spriteMap[arcade::TileType::POWERUP][2] = 0.0f;

    spriteMap[arcade::TileType::PLAYER][0] = 1.0f;
    spriteMap[arcade::TileType::PLAYER][1] = 1.0f;
    spriteMap[arcade::TileType::PLAYER][2] = 1.0f;

    spriteMap[arcade::TileType::EMPTY][0] = 0.0f;
    spriteMap[arcade::TileType::EMPTY][1] = 0.0f;
    spriteMap[arcade::TileType::EMPTY][2] = 0.0f;
    _ratiox = 1.22;
    _ratioy = 2.42;
  }
  else if (gameName.compare("pacman") == 0)
  {
    spriteMap[arcade::TileType::BLOCK][0] = 0.0f;
    spriteMap[arcade::TileType::BLOCK][1] = 0.0f;
    spriteMap[arcade::TileType::BLOCK][2] = 1.0f;

    spriteMap[arcade::TileType::EVIL_DUDE][0] = 0.0f;
    spriteMap[arcade::TileType::EVIL_DUDE][1] = 1.0f;
    spriteMap[arcade::TileType::EVIL_DUDE][2] = 1.0f;

    spriteMap[arcade::TileType::PLAYER][0] = 1.0f;
    spriteMap[arcade::TileType::PLAYER][1] = 1.0f;
    spriteMap[arcade::TileType::PLAYER][2] = 0.2f;

    spriteMap[arcade::TileType::OTHER][0] = 1.0f;
    spriteMap[arcade::TileType::OTHER][1] = 0.6f;
    spriteMap[arcade::TileType::OTHER][2] = 0.2f;

    spriteMap[arcade::TileType::POWERUP][0] = 0.0f;
    spriteMap[arcade::TileType::POWERUP][1] = 1.0f;
    spriteMap[arcade::TileType::POWERUP][2] = 0.0f;

    spriteMap[arcade::TileType::EMPTY][0] = 0.0f;
    spriteMap[arcade::TileType::EMPTY][1] = 0.0f;
    spriteMap[arcade::TileType::EMPTY][2] = 0.0f;
    _ratiox = 1.6;
    _ratioy = 3.2;
  }
}

arcade::CommandType		arcade::libopengl::getEvent()
{
  arcade::CommandType   save;

  glutMainLoopEvent();
  if (key == arcade::CommandType::SWITCH_GAME_NEXT || key == arcade::CommandType::SWITCH_GAME_PREV || key == arcade::CommandType::RESTART)
  {
    save = key;
    key = arcade::CommandType::UNDEFINED;
    return (save);
  }
  return (key);
}

extern "C" arcade::libopengl *getLib()
{
  std::cout << "Loading libopengl..."  << std::endl;
  arcade::libopengl *_new = new arcade::libopengl();
  return (_new);
}
