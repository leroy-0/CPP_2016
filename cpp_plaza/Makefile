NAME	= plazza

CC	= g++

RM	= rm -f

SRCS	= ./src/Manager.cpp \
	  ./src/main.cpp \
	  ./src/Command.cpp \
	  ./src/Reception.cpp \
	  ./src/Error.cpp

OBJS	= $(SRCS:.cpp=.o)


CPPFLAGS = -I./include/
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

ui:
	$(MAKE) -C ./GUI/

re: fclean all

.PHONY: all clean fclean re
