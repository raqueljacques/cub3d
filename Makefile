# Nome do executável
NAME        = cub3d

# Compilador e flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Diretórios principais
SRC_DIR     = src
INC_DIR     = includes
LIBFT_DIR   = libraries/libft
MLX_DIR     = libraries/minilibx

# Arquivos das bibliotecas
LIBFT       = $(LIBFT_DIR)/libft.a
MLX_LIB     = $(MLX_DIR)/libmlx.a

# Flags extras para linkar a MinilibX no Linux
MLXFLAGS    = -L$(MLX_DIR) -Lmlx -lmlx_Linux -lX11 -lXext

# Includes do projeto + libft + minilibx
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Lista de todos os .c encontrados em src/
SRCS        = $(shell find $(SRC_DIR) -type f -name "*.c")

# Converte todos .c em .o
OBJS        = $(SRCS:.c=.o)

# Comando de remover
RM          = rm -f

# Regra padrão: compila tudo
all: $(NAME)

# Como gerar o executável
$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo "🔗 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "✅ $(NAME) is ready."

# Compila a libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compila a minilibx
$(MLX_LIB):
	@make -C $(MLX_DIR)

# Regra genérica para compilar arquivos .c em .o
%.o: %.c
	@echo "🛠️  Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Remove objetos
clean:
	@echo "🧹 Cleaning object files..."
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@$(RM) $(OBJS)

# Remove objetos e binário
fclean: clean
	@echo "🧹 Removing  $(NAME)..."
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

# Recompila tudo do zero
re: fclean all

# Declara regras que não são arquivos
.PHONY: all clean fclean re