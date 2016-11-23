NAME =			avm

CC =			g++ $(FLAGS) $(INCLUDES)

INCLUDES =		-I./includes

SRC =			src/main.cpp \
				src/AbstractException.cpp \
				src/Controller.cpp \
				src/Factory.cpp \
				src/Lexer.cpp \
				src/Parser.cpp \
				src/Vm.cpp
				

OBJ =			$(SRC:%.cpp=%.o)


FLAGS =			-Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJ) 
				$(CC) $(OBJ) -o $(NAME)

clean:
				rm -f $(OBJ)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

%.o:			%.cpp
				$(CC) -c $< -o $@