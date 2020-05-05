NAME	= ../plaza

CC	= g++

RM	= rm -f

SRCS	= ./src/main.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I -lnana -lX11 -lpthread -lrt -lXft -lstdc++fs
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) -lnana -lX11 -lpthread -lrt -lXft -lstdc++fs

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
