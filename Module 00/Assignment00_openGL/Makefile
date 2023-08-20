#* TARGET *#
TARGET = project00.exe

#*SOURCE FILES *#
FILES = main.cpp glad.cpp App.cpp
		
SRC = $(addprefix srcs/, $(FILES))

#* OBJECT FILES *#
OBJ_DIR = obj
OBJS = $(SRC:srcs/%.cpp=$(OBJ_DIR)/%.o)

#* FLAGS *#
FLAGS = -Wall -Wextra -Werror

#* HEADER FILES *#
INCLUDE = include/

#* LIBRARY *#
LIB = lib/

#* DELETE *#
DEL = rm -rf

all: $(TARGET)

$(OBJ_DIR)/%.o: srcs/%.cpp
	g++ $(FLAGS) -c -I $(INCLUDE) -L $(LIB) -lglfw3dll $< -o $@

$(TARGET): $(OBJS) $(INCLUDE)
	g++ $(FLAGS) -I $(INCLUDE) -L $(LIB) $(OBJS) -lglfw3dll -o $(TARGET)

re: fclean all

clean:
	$(DEL) $(OBJS)

fclean:	clean
	$(DEL) $(TARGET)

.PHONY: clean fclean re all