.SILENT:
.PHONY: all init clean fclean re FORCE

include config.mk
include minishell.mk

OBJS := $(patsubst $(SRCSDIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): libft/libft.a Makefile $(OBJS) | $(EXEC_DIR)
	echo "$(PURPLE)Compiling $(NAME) in progress...$(RESET)"

		$(CC) $(CFLAGS) $(CPPFLAGS) -o $(EXEC) $(OBJS) -L libft -lft $(RLFLAGS)

	echo "$(GREEN)$(EXEC) completed successfully!$(RESET)"

	echo "$(GREEN)"
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

libft/libft.a: FORCE
	$(MAKE) -C libft

$(OBJS_DIR)%.o: $(SRCSDIR)%.c | $(OBJS_DIR)
	mkdir -p $(dir $@)
	echo "$(PURPLE)Compiling $<...$(RESET)"

		$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

	echo "$(GREEN)$< completed successfully!$(RESET)"

$(OBJS_DIR):
	echo "$(YELLOW)Creating directory $(OBJS_DIR)...$(RESET)"
		
		mkdir -p $(OBJS_DIR)

$(EXEC_DIR):
	echo "$(YELLOW)Creating $(EXEC_DIR) directory...$(RESET)"

		mkdir -p $(EXEC_DIR)

clean:
	$(RM_DIR) $(OBJS_DIR)
	$(MAKE) -C $(DIR_LIBFT) clean
	echo "$(RED)Cleaning of .o and .d files completed successfully! ／人◕ ‿‿ ◕人＼$(RESET)"

fclean: clean
	$(RM_DIR) $(EXEC_DIR)
	$(MAKE) -C $(DIR_LIBFT) fclean
	echo "$(RED)"
	echo "┌──────────────────────────────────────────────────────────┐"
	echo "│      Deletion finished successfully! ( ◔ ω ◔) ノシ         │"
	echo "└──────────────────────────────────────────────────────────┘"
	echo "                           ╱|、"
	echo "                         (˚ˎ 。7"
	echo "                          |、˜|"
	echo "                         じしˍ,)ノ"
	echo "$(RESET)"

re: fclean all

FORCE:
