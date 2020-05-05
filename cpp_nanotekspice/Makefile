NAME_LIB = libnanotekspice.a

AR	= ar rc

RAN	= ranlib

NAME	= nanotekspice

CC	= g++

RM	= rm -f

SRCS_L	= ./src/Component.cpp \
	  ./src/Pin.cpp \
	  ./src/parser.cpp \
	  ./src/parser_tools.cpp \
	  ./src/Error.cpp \
	  ./src/C4081.cpp \
	  ./src/C4071.cpp \
	  ./src/C4011.cpp \
	  ./src/C4001.cpp \
	  ./src/C4030.cpp \
	  ./src/C4069.cpp \
	  ./src/C4514.cpp \

SRCS_N 	= ./src/main.cpp \

OBJS_L	= $(SRCS_L:.cpp=.o)

OBJS_N  = $(SRCS_N:.cpp=.o)

CPPFLAGS = -I./include/
CPPFLAGS += -W -Wall -Wextra

all: $(NAME) $(NAME_LIB)

$(NAME): $(OBJS_L) $(OBJS_N)
	 $(CC) $(OBJS_N) $(OBJS_L) -o $(NAME)

$(NAME_LIB): $(OBJS_L)
	     $(AR) $(NAME_LIB) $(OBJS_L)
	     $(RAN) $(NAME_LIB)

clean:
	$(RM) $(OBJS_L)
	$(RM) $(OBJS_N)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_LIB)

re: fclean all

.PHONY: all clean fclean re
