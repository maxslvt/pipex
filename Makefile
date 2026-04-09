NAME = pipex

CFLAGS = -Wall -Wextra -Werror -g3 -I src

SRC = src/main.c \
	src/utils.c

OBJETS = $(SRC:.c=.o)

LIBFT_DIR = ./src/libft/

LIBFT = libft.a

RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
WHITE=\033[1;37m

$(NAME): $(LIBFT_DIR)$(LIBFT) $(OBJETS)
	@printf "\r\033[K🟡 ${YELLOW}[PIPEX] Compiling pipex...${WHITE}\n"
	@cc $(CFLAGS) -o $(NAME) $(OBJETS) $(LIBFT_DIR)$(LIBFT)
	@printf "\r\033[K✅ ${GREEN}[PIPEX] Compiled !${WHITE}\n"

$(LIBFT_DIR)$(LIBFT):
	@make -s -C $(LIBFT_DIR) --no-print-directory

.c.o:
	@printf "\r🟡 ${MAGENTA}[COMPILING📦] $<${WHITE}"
	@cc ${CFLAGS} -c $< -o $@

all: $(NAME)

clean:
	@printf "🟡 ${MAGENTA}[CLEANING🧹] pipex object files...${WHITE}\n"
	@rm -f $(OBJETS) src/*.o
	@printf "✅ ${GREEN}[CLEANED🧹]${WHITE}\n"

fclean: clean
	@printf "🟡 ${MAGENTA}[CLEANING🧹] libft and executable...${WHITE}\n"
	@make -s -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)
	@printf "✅ ${GREEN}[CLEANED🧹]${WHITE}\n"

re: fclean all

.PHONY: all clean fclean re