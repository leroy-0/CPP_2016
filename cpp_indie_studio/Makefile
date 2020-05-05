##
## 
## Made by leroy_0
## Login   <maxime.leroy@epitech.eu>
## 
## Started on  Wed May 31 15:39:14 2017 leroy_0
## Last update Sun Jun 18 18:20:32 2017 Sebastien
##

NAME	= Bomberman

CC	= g++ -g

RM	= rm -f

SRCS	= ./src/EntityManager.cpp \
	  ./src/PowerUpManager.cpp \
	  ./src/Main.cpp \
	  ./src/Bomberman.cpp \
	  ./src/Map.cpp \
	  ./src/Entity.cpp \
	  ./src/Bomb.cpp \
	  ./src/Player.cpp \
	  ./src/Wall.cpp \
	  ./src/Save.cpp \
	  ./src/GUI.cpp \
	  ./src/Input.cpp \
	  ./src/Powerup.cpp \
	  ./src/pSpeedUp.cpp \
	  ./src/pSpeedDown.cpp \
	  ./src/pBombRangeUp.cpp \
	  ./src/pBombRangeDown.cpp \
	  ./src/pBombUp.cpp \
	  ./src/pBombDown.cpp \
	  ./src/Explosion.cpp \
	  ./src/BomberIA.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I./include/ -I/usr/local/include/cegui-0/ -I/usr/include/cegui-0/ -I./bin/irrKlang/

CPPFLAGS += -W -Wall -Wextra -std=c++11

LDFLAGS		+= 	-lOgreTerrain
LDFLAGS    	+= 	-lOgreOverlay
LDFLAGS		+= 	-lOgreMain
LDFLAGS		+= 	-lOIS
LDFLAGS		+=	-lboost_system
LDFLAGS		+=	-lCEGUIBase-0
LDFLAGS		+= 	-lCEGUIOgreRenderer-0
LDFLAGS		+= 	-lboost_thread
LDFLAGS		+= 	"lib/libIrrKlang.so"

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
