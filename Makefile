NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

SRC_DIR     = src
INC_DIR     = includes
LIBFT_DIR   = libraries/libft
MLX_DIR     = libraries/minilibx

LIBFT       = $(LIBFT_DIR)/libft.a
MLX_LIB     = $(MLX_DIR)/libmlx.a

MLXFLAGS    = -L$(MLX_DIR) -Lmlx -lmlx_Linux -lX11 -lXext

INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS        = $(shell find $(SRC_DIR) -type f -name "*.c")

OBJS        = $(SRCS:.c=.o)

RM          = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo "🔗 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -lm -o $(NAME)
	@echo "✅ $(NAME) is ready."

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

%.o: %.c
	@echo "🛠️  Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@echo "🧹 Removing  $(NAME)..."
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
