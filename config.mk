NAME            := minishell
EXEC            := exec/$(NAME)
OBJS_DIR        := .objs/
EXEC_DIR        := exec/
DIR_LIBFT		:= libft/

CC              := cc
MAKE            := make
RM              := rm -f
RM_DIR          := rm -rf

RLFLAGS         := -lreadline
CFLAGS          := -Wall -Wextra -Werror -g3
CPPFLAGS		:= -MMD -MP -I include/ -I libft/include/
INC             := -I./include
INCLUDE         := include/

PURPLE          := \033[1;35m
GREEN           := \033[1;32m
RED             := \033[1;31m
YELLOW          := \033[33m
BOLD_UNDERLINE  := \033[1;4m
RESET           := \033[0m