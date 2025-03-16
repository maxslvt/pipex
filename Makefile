NAME = pipex

CC = clang

CFLAGS = -Werror -Wextra -Wall -g

SRC = src/pipex.c src/ft_utils.c src/ft_token.c src/ft_strtrimtoken.c

OBJS = $(SRC:.c=.o)

LIBFTDIR = ./src/libft/

LIBFT = libft.a

RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
WHITE=\033[1;37m

$(NAME) : $(OBJS)
	@make -s -C $(LIBFTDIR) --no-print-directory
	@printf "\r\033[K🟡 ${YELLOW}[PIPEX] Compiling ${NAME}...${WHITE}\n"
	@$(CC) $(OBJS) $(LIBFTDIR)$(LIBFT) -o $(NAME)
	@printf "\r\033[K✅ ${GREEN}[PIPEX] Compiled !${WHITE}\n"

all : $(NAME)

libft:
	make -s -C $(LIBFTDIR)

.c.o :
	@printf "\r🟡 ${MAGENTA}[COMPILING📦] $<${WHITE}"
	@$(CC) $(CFLAGS) -g -c -o $@ $<

clean :
	@printf "🟡 ${MAGENTA}[CLEANING🧹] .o files...${WHITE}\n"
	@rm -f $(OBJS)
	@printf "✅ ${GREEN}[CLEANED🧹]${WHITE}\n"

fclean : clean
	@printf "🟡 ${MAGENTA}[CLEANING🧹] libft...${WHITE}\n"
	@rm -f $(NAME)
	@make -s -C $(LIBFTDIR) fclean
	@printf "✅ ${GREEN}[CLEANED🧹]${WHITE}\n"

re : fclean all

.PHONY : all clean fclean re
