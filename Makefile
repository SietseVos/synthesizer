NAME = synthesizer

SRC = main.c saw.c square.c triangle.c

OBJ = $(SRC:.c=.o)

LIB = -lportaudio -lrt -lasound -pthread -lm

INCLUDE = -I/include -L/lib 

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) $(INCLUDE) $(LIB) -o $(NAME)

%.o: src/%.c
	gcc -c $< $(INCLUDE) $(LIB)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
re: fclean all
