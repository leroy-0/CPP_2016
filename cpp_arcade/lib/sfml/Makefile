NAME    = ../lib_arcade_sfml.so

CC      = g++

RM      = rm -f

SRCS    = ./src/arcade_libsfml.cpp

OBJS    = $(SRCS:.cpp=.o)

CPPFLAGS = -I./inc/ -I../inc/ -I../../inc/
CPPFLAGS += -W -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -fPIC

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -shared -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
