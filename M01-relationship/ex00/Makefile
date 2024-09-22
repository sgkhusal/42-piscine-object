NAME    = ex.exe

CC      = c++
CFLAGS  = -g3 -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP
SRC     =	main.cpp test_utils.cpp
INC     =	test_utils.hpp \
			Postion.hpp \
			Statistic.hpp \
			Worker.hpp \
			Tool.hpp \
			Shovel.hpp \
			Hammer.hpp
INCPATH = -I./src

OBJDIR  = obj
OBJ     = $(SRC:%.cpp=$(OBJDIR)/%.o)
DEPS    = $(SRC:%.cpp=$(OBJDIR)/%.d)

vpath %.cpp src
vpath %.hpp src

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCPATH)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

re: fclean all

run: all
	./$(NAME)

-include $(DEPS)
