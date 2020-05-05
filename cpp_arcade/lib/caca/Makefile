NAME	= ../lib_arcade_libcaca.so

CC	= g++ `pkg-config --libs caca`

RM	= rm -f

SRCS	= ./src/arcade_libcaca.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I./inc/ -I./../../games/commons/inc -I./../../inc/
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) -shared -o $(NAME) -fPIC $(SRCS) -I./inc/  -I./../../games/commons/inc -I./../../inc/

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re
