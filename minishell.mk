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
	utils/commands_gestionary \
	utils/free_commands \
	utils/struct_to_char \
	process/process_heredoc \
	process/process_pipe \
	process/process_quotes \
	process/process_redirect \
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
	process/process_word \
	process/process_string \


SRC += $(addprefix $(SIGNALDIR), $(addsuffix .c, $(SIGNALSRC)))

override SIGNALSRC := \
	signal \


SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC := \
	env \

SRC += $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

override EXECSRC := \
	child_dup \
	child_pathed \
	child_utils \
	child \
	exec \
	redirections \


# SRC += $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))

# override BUILTINSRC := \
# 	cd \
# 	echo \
# 	env \
# 	exit \
# 	# export \
# 	# pwd \
# 	# unset \

