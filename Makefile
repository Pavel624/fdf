NAME = fdf

SRC  = main.c

OBJ  = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

FRAMEWORKS = -framework OpenGL -framework AppKit

LIBFT = libft/libft.a
MINILIBX = minilibx/libmlx.a

INC_LIB = libft

HEAD = libft/libft.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(MINILIBX) $(FRAMEWORKS) -I$(INC_LIB) -o $(NAME)
	
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
