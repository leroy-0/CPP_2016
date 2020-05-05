NAME    = ../lib_arcade_opengl.so

CC      = g++

RM      = rm -f

SRCS    = ./src/arcade_libopengl.cpp

OBJS    = $(SRCS:.cpp=.o)

CPPFLAGS = -I./inc/ -I../inc/ -I../../inc/
CPPFLAGS += -W -Wall -Wextra -lGL -lGLU -lglfw3 -lX11 -lglut -lXxf86vm -lXrandr -pthread -lXi -ldl -lXinerama -lXcursor -fPIC

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -shared -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
