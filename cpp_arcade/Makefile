NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./src/Error.cpp \
	  ./src/Main.cpp \
	  ./src/Manager.cpp \
          ./src/Core.cpp

OBJS	= $(SRCS:.cpp=.o)

LDFLAGS = -ldl
CPPFLAGS = -I./inc/ -I./games/commons/inc -g
CPPFLAGS += -W -Wall -Wextra

all:	$(NAME)
	$(MAKE) -C ./games/

lib:	$(NAME)
	$(MAKE) -C ./lib/caca
	$(MAKE) -C ./lib/sfml
	$(MAKE) -C ./lib/opengl

$(NAME): $(OBJS)
	 $(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C ./games/ clean
	$(MAKE) -C ./lib/caca clean
	$(MAKE) -C ./lib/sfml clean
	$(MAKE) -C ./lib/opengl clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C ./games/ fclean
	$(MAKE) -C ./lib/caca fclean
	$(MAKE) -C ./lib/sfml fclean
	$(MAKE) -C ./lib/opengl fclean


re: fclean all

.PHONY: all clean fclean re
