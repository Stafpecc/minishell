#Config#
NAME        = minishell_test
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I./include -I./libft/includes
LIBFT_DIR   = ./../../libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCDIR      = ./
SRC_FILES   = child_dup.c \
              child_pathed.c \
              child_utils.c \
              child.c \
              exec.c
SRCS        = $(addprefix $(SRCDIR)/, $(SRC_FILES)) main.c
OBJS        = $(SRCS:.c=.o)

#Rules#
.PHONY: all clean fclean re libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
