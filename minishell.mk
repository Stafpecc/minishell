override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override PARSERDIR	:= parsing/
override LEXERDIR	:= lexer/
override EXECDIR	:= exec/
override BUILTINDIR := builtin/
override ENVDIR 	:= env/
override SIGNALDIR	:= signal/
override UTILSDIR   := utils/

SRC += $(addprefix $(MAINDIR), $(addsuffix .c, $(MAIN)))

override MAIN := \
	main \

SRC += $(addprefix $(PARSERDIR), $(addsuffix .c, $(PARSERSRC)))

override PARSERSRC := \
	parser \
	launcher \
	expand/expand \
	expand/expand_utils \
	expand/get_env_value \
	parse/parse_launch \
	parse/parse_dir \
	parse/parse_file \
	parse/parse_utils \
	utils/commands_gestionary \
	utils/free_commands \
	utils/struct_to_char \
	utils/struct_to_char_utils \
	utils/dup_targ_to_tredirect_array \
	process/process_pipe \
	process/process_quotes \
	process/process_redirect \
	process/process_add_redirect \
	process/process_word_string \
	process/process_utils \


SRC += $(addprefix $(LEXERDIR), $(addsuffix .c, $(LEXERSRC)))

override LEXERSRC := \
	lexer \
	launcher \
	utils/token_gestionary \
	utils/token_utils \
	utils/free_token \
	process/process_word_string \
	process/process_quotes \


SRC += $(addprefix $(SIGNALDIR), $(addsuffix .c, $(SIGNALSRC)))

override SIGNALSRC := \
	signal \


SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC := \
	env \

SRC += $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

override EXECSRC := \
	child_dup_utils \
	child_dup \
	child_err_msg \
	child_execute \
	child_maker \
	child_maker_helper \
	child_utils \
	child_wait \
	child \
	exec_utils\
	exec \
	here_doc\
	single_builtin \


SRC += $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))

override BUILTINSRC := \
	cd_utils \
	cd \
	echo \
	env \
	exit \
	exit_utils \
	export \
	export_utils \
	pwd \
	unset \


SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC := \
	check_error \
	execute \
	free \
	launch_lexer \
	minishell_loop \
	loop_helper \
	quotes \
	t_utils \
