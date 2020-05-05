NAME	= ../lib_arcade_pacman.so

CC	= g++

RM	= rm -f

SRCS	= ./src/Pacman.cpp \
		  ./src/Pacmap.cpp \
		  ./src/PacEnnemy.cpp \
	  ./../commons/src/Character.cpp \
	  ./../commons/src/Map.cpp \

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -W -Wall -Wextra -I./../commons/inc/ -I./inc/ -I./../../inc/ -fPIC 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared  -o  $(NAME)  $(SRCS) -I./../commons/inc/ -I./inc/ -I./../../inc/ -fPIC 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
