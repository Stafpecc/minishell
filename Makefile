.SILENT:
.PHONY: all clean fclean re

#==============================================================================#
#                                VARIABLES                                     #
#==============================================================================#

NAME        := minishell
EXEC        := exec/$(NAME)

OBJS_DIR    := .objs/
EXEC_DIR    := exec/

include config.mk

include rules/main.mk
include rules/parsing.mk
include rules/lexer.mk
include rules/exec.mk
include rules/builtin.mk
include rules/env.mk

OBJS		= $(patsubst %.c, .objs/%.o, $(SRC))

#==============================================================================#
#                              BUILD RULES                                     #
#==============================================================================#

all: $(NAME)

$(NAME): $(OBJS) | $(EXEC_DIR)
	echo "$(PURPLE)Compiling $(NAME) in progress...$(RESET)"
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBS)
	echo "$(GREEN)$(EXEC) completed successfully!"
	echo "┌───────────────────────────────────────────────────────────┐"
	echo "│      Compilation finished successfully! ᕕ(⌐■_■)ᕗ ♪♬       │"
	echo "└───────────────────────────────────────────────────────────┘"

	echo "                      ☆  *    .      ☆"
	echo "                        ∧＿∧   ∩    * ☆"
	echo "                 *  ☆ ( ・∀・)/ ."
	echo "                  .  ⊂      ノ* ☆"
	echo "                ☆ * (つ   ノ  .☆"
	echo "                      (ノ"

	echo "$(RESET)"

$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	echo "$(PURPLE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	echo "$(GREEN)$< compiled successfully!$(RESET)"

#==============================================================================#
#                              DIRECTORY CREATION                              #
#==============================================================================#

$(OBJS_DIR):
	echo "$(YELLOW)Creating $(OBJS_DIR)...$(RESET)"
	mkdir -p $(OBJS_DIR)

$(EXEC_DIR):
	echo "$(YELLOW)Creating $(EXEC_DIR)...$(RESET)"
	mkdir -p $(EXEC_DIR)

#==============================================================================#
#                              CLEAN RULES                                     #
#==============================================================================#

clean:
	echo "$(RED)Deleting object files...$(RESET)"
	$(RM_DIR) $(OBJS_DIR)
	$(RM) massif.out*
	echo "$(GREEN)Object files deleted!$(RESET)"

fclean: clean
	echo "$(RED)Deleting $(NAME)...$(RESET)"
	$(RM_DIR) $(EXEC_DIR)
	echo "$(GREEN)$(NAME) deleted!$(RESET)"
	echo "$(RED)┌──────────────────────────────────────────────────────────┐"
	echo "│      Deletion finished successfully! ( ◔ ω◔) ノシ        │"
	echo "└──────────────────────────────────────────────────────────┘"
	echo "                          ╱|、"
	echo "                        (˚ˎ 。7"
	echo "                         |、˜|"
	echo "                        じしˍ,)ノ"
	echo "$(RESET)"

re: fclean all
