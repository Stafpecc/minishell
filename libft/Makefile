.SILENT:
NAME=libft.a

#------------------------------------------------------------------------------#
# 							VARIABLES										   #
#------------------------------------------------------------------------------#

SRCS_DIR= ./cfiles

SRCS = \
	ft_isdigit.c                      \
	ft_isalpha.c                      \
	ft_isalnum.c                      \
	ft_isascii.c                      \
	ft_isprint.c                      \
	ft_strlen.c                       \
	ft_memset.c                       \
	ft_bzero.c                        \
	ft_memcpy.c                       \
	ft_memmove.c                      \
	ft_strlcpy.c                      \
	ft_strlcat.c                      \
	ft_toupper.c                      \
	ft_tolower.c                      \
	ft_strchr.c                       \
	ft_strrchr.c                      \
	ft_strncmp.c                      \
	ft_memchr.c                       \
	ft_memcmp.c                       \
	ft_strnstr.c                      \
	ft_atoi.c                         \
	ft_strdup.c                       \
	ft_calloc.c                       \
	ft_split.c                        \
	ft_substr.c                       \
	ft_strjoin.c                      \
	ft_strtrim.c                      \
	ft_itoa.c                         \
	ft_putchar_fd.c                   \
	ft_putstr_fd.c                    \
	ft_putendl_fd.c                   \
	ft_putnbr_fd.c                    \
	ft_strmapi.c                      \
	ft_striteri.c                     \
	ft_printf.c 		              \
	ft_putchar.c 			          \
	ft_putstr.c 			          \
	ft_putnbrbase.c 		          \
	ft_handle.c                       \
	ft_lstnew_bonus.c                 \
	ft_lstadd_front_bonus.c           \
	ft_lstsize_bonus.c                \
	ft_lstlast_bonus.c                \
	ft_lstadd_back_bonus.c            \
	ft_lstdelone_bonus.c              \
	ft_lstclear_bonus.c               \
	ft_lstiter_bonus.c                \
	ft_lstmap_bonus.c 				  \
	ft_atoi_only_num.c				  \
	ft_strcmp.c						  \
	ft_pass.c 					      \
	ft_atof.c						  \
	ft_atod.c						  \
	ft_realloc.c

SRCS:= $(SRCS:%=$(SRCS_DIR)/%)

OBJS_DIR= ./OBJS

OBJS=$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INCS= includes

DEPS= $(OBJS:.o=.d)

PURPLE          = \033[1;35m
GREEN           = \033[1;32m
RESET           = \033[0m

#------------------------------------------------------------------------------#
# 							COMMANDS									       #
#------------------------------------------------------------------------------#

CC= cc

CFLAGS= -Werror -Wextra -Wall -pg

RM= rm -rf

CFSIGSEV = -fsanitize=address

DIR_DUP= mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

#------------------------------------------------------------------------------#
# 							RULES											   #
#------------------------------------------------------------------------------#

all:$(NAME)


$(NAME): $(OBJS) $(INCS)/$(INC_NAME)
		$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@

fsanitize:
	$(MAKE) CFLAGS="$(CFLAGS) $(CFSIGSEV)"

clean:
	$(RM) $(OBJS_DIR)

fclean:clean
	$(RM) $(NAME)
	rm -f a.out

re:fclean all

.PHONY: all clean fclean re