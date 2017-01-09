NAME = fractol

FLG = -Wall -Wextra -Werror

SRC = srcs/main.c \
	  srcs/fractol_gen.c \
	  srcs/fractol_event.c \
	  srcs/mandelbrot.c \
	  srcs/julia.c \
	  srcs/buddhabrot.c \


OBJ = $(SRC:%.c=%.o)

INC = -I./includes \
	  -I./engine/libft/includes \
	  -I./engine/includes \
	  -I/usr/include \
	  -I/Library/Frameworks/SDL2.framework/Headers \

LIB = -L./engine/libft \
	  -L./engine \
	  -L/Library/Frameworks/SDL2.framework \

all: $(NAME)

$(NAME):
	make -C engine 
	gcc $(FLG) $(LIB) $(INC) $(SRC) -lm -lengine -lft -framework SDL2 -o $(NAME) -O3

debug:
	make -C engine 
	gcc $(FLG) $(LIB) $(INC) $(SRC) -lm -lengine -lft -framework SDL2 -o $(NAME) -O3 -g


clean:
	make -C engine clean
	rm -f $(NAME)

fclean: clean
	make -C engine fclean
	rm -rf $(OBJ)

re: clean all
