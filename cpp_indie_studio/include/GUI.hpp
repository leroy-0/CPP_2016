/*
** GUI.hpp for cpp_indie_studio in /home/kleinh/Documents/cpp_indie_studio/include/GUI.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Tue Jun 13 12:32:21 2017 Arthur Klein
** Last update Tue Jun 13 12:32:21 2017 Arthur Klein
*/

#ifndef PROJECT_GUI_HPP
#define PROJECT_GUI_HPP

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <dirent.h>


namespace					IndieGame
{

  enum						state
  {
    MENU,
    CREDITS,
    GAME,
    OPTION,
    PAUSE,
    LOOP,
    EXIT,
    CHOOSEPLAYER,
    IA,
    LOAD,
    SPLASH
  };
  class						GUI
  {
  public:
    bool					_drawMap;
  protected:
    CEGUI::OgreRenderer				*_renderer;
    int						_w;
    int						_h;
    CEGUI::Window 				*_rootWindow;
    CEGUI::GUIContext				*_context;
    CEGUI::Window				*_quit;
    CEGUI::Window				*_text;
    DIR						*_dir;
    CEGUI::Window				*_defaultContainer;
    CEGUI::Window				*_playerContainer;
    CEGUI::Window				*_IAContainer;
    CEGUI::Window				*_loadContainer;
    CEGUI::Window				*_pauseContainer;
    CEGUI::Window				*_textContainer;
    CEGUI::Window				*_optionContainer;
    unsigned int				_nbPlayers;
    int						_nbIA;
    bool					_isPlayabled;
    bool					_newGame;
    bool					_wantSave;
    bool					_sound;
    std::string					_save;
    struct dirent				*_ent;
    std::map					<std::string, CEGUI::Window *>_buttonMap;
    std::map					<std::string, CEGUI::Window *>_buttonIA;
    std::map					<std::string, CEGUI::Window *>_buttonLoad;
    std::map					<std::string, CEGUI::Window *>_buttonOption;
    std::vector<std::string>			_files;
    IndieGame::state				state;
  public:
    GUI(Ogre::Root	*Root, int w, int h);
    ~GUI();

    /* CREATING BUTTON FUNCTION */
  public:
    bool					createButtonForMenu();
    bool					createText();
    void					createSaveDir();
    bool					createButtonLoad();
    bool					createButtonForPause();
    bool					createButtonForChoosePlayer();
    bool					createButtonForIA();
    bool					createButtonForOption();

  public:
    void					displayButton();
    void					displayText();

    /* EVENT STATE */
  public:
    bool					isAllMenuDesactived() const;
    bool					mouseMoved(const OIS::MouseState &arg);
    bool					isButtonExitPressInMenu() const;
    IndieGame::state				whereIsMouse(const OIS::MouseState &arg);
    void					iaState();
    void					menuState();
    void					pauseState();
    void					playerState();
    void					gameState();
    void					loadState();
    void					optionState();

    /* SETTER */
  public:
    void					setMytext(const std::string &text, const CEGUI::USize size, int pos1, int pos2);
    void					setPropetyButton(std::string name , std::string text, CEGUI::USize size , CEGUI::UVector2 position,  bool state);
    void					setState(IndieGame::state);
    void					setDrawMap(bool draw);
    void					setNbPlayers(unsigned int nbPlayers);
    void					setNewGame(bool newGame);
    void					setWantSave(bool wantSave);
    void					setNbIA(int nbIA);
    void					setNbButtonIa();
    void					setTextForLoadButton();
    void					setValueByDefault();
    void					setSave(const std::string &save);

    /* STATE OF GAME */
  public:
    bool					isPlayable() const;
    bool					isMenu() const;
    bool					isLoadGame() const;
    bool					isPause() const;
    bool					isOption() const;
    bool					isGame() const;
    bool					isChoosePlayer() const;

    /* GETTER */
  public:
    IndieGame::state 				getState() const;
    bool 					getSound() const;
    const CEGUI::Window				&getText() const;
    const CEGUI::Window				&getTextContainer() const;
    bool					getNewGame() const;
    bool					getWantSave() const;
    unsigned int				getNbPlayers() const;
    bool					getDrawMap() const;
    const CEGUI::Window				&getChoosePlayerContainer() const;
    const CEGUI::Window				&getPauseContainer() const;
    const CEGUI::Window				&getDefaultContainer() const;
    const CEGUI::Window				&getIAContainer() const;
    int						getNbIA() const;
    std::vector<std::string>			getSaveInDir();
    std::string					getSave() const;
    std::map<std::string, CEGUI::Window *>	getLoadButton() const;
  };
}
#endif //PROJECT_GUI_HPP
