override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override PARSERDIR	:= parsing/
override LEXERDIR	:= lexer/
override EXECDIR	:= exec/
override BUILTINDIR := builtin/
override ENVDIR 	:= env/
override SIGNALDIR	:= signal/

SRC += $(addprefix $(DEBUGDIR), $(addsuffix .c, $(DEBUG)))

override DEBUG := \
	debug \


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
	parse/parse_redirect \
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


SRC += $(addprefix $(SIGNALDIR), $(addsuffix .c, $(SIGNALSRC)))

override SIGNALSRC := \
	signal \


SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC := \
	env \

SRC += $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

override EXECSRC := \
	child_dup \
	child_maker \
	child_pathed \
	child_utils \
	child \
	exec_utils\
	exec \
	here_doc\
	redirections \
	single_builtin \


SRC += $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))

override BUILTINSRC := \
	cd_utils \
	cd \
	echo \
	env \
	exit \
	export \
	pwd \
	unset \

