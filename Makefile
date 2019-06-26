NAME = fdf

SRC  = main.c reader.c additional.c drawer.c matrixes.c initialize.c

OBJ  = $(SRC:.c=.o)

FLAGS = -Wall -g

LIBFLAGS = -framework OpenGL -framework AppKit -lm -lmlx #-L minilibx -l mlx -lm # macOS
#LIBFLAGS = -lmlx -lXext -lX11 minilibx/libmlx.a -lm # for Linux

LIBFT = libft/libft.a

INC_LIB = libft

HEAD = libft/libft.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(LIBFLAGS) -I$(INC_LIB) -o $(NAME)
	
$(LIBFT):
	make -C libft/

%.o : %.c
	gcc $(FLAGS) -c $< -o $@ -I$(INC_LIB)

clean:
	make -C libft clean
	rm -f *.o

fclean: clean
	make -C libft fclean
	rm -f $(OBJ)
	rm -f $(NAME)

re: fclean all
	make -C libft re
