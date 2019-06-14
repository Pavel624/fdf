NAME = fdf

SRC  = main.c reader.c additional.c drawer.c

OBJ  = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -g

LIBFLAGS = -framework OpenGL -framework AppKit -L minilibx -I minilibx -lmlx
#LIBFLAGS = -lmlx -lXext -lX11 minilibx/libmlx.a

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
