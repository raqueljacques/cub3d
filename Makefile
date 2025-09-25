CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = cub3d

RM = rm -f

SRCS =

OBJS = ${SRCS:.c=.o}

INCLUDES = -I includes -I libft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS)
	@echo "$(NAME) is ready!"

$(LIBFT):
@make -C $(LIBFT_DIR)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

	clean:
	@echo "Cleaning object files..."
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@echo "Removing $(NAME)..."
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re