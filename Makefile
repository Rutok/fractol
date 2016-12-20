NAME = fractol

FLG = -Wall -Wextra -Werror

SRC = srcs/engine.c \
	  srcs/error.c \
	  srcs/event.c \
	  srcs/drawer.c \
	  srcs/fractol_gen.c \
	  srcs/fractol_event.c \
	  srcs/main.c \

OBJ = $(SRC:%.c=%.o)

INC = -I./includes \
	  -I./libft/includes \
	  -I/usr/include \
	  -I/usr/include/SDL2

LIB = -L./libft

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(FLG) $(SRC) $(INC) $(LIB) -lm -lft -lSDL2 -o $(NAME) -O3

clean:
	make -C libft clean
	rm -f $(NAME)

fclean: clean
	make -C libft fclean
	rm -rf $(OBJ)

re: clean all
