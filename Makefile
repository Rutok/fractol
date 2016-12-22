NAME = fractol

FLG = -Wall -Wextra -Werror

SRC = srcs/engine.c \
	  srcs/drawer.c \
	  srcs/event.c \
	  srcs/error.c \
	  srcs/main.c \
	  srcs/fractol_gen.c \
	  srcs/fractol_event.c \
	  srcs/mandelbrot.c \
	  srcs/julia.c \


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
