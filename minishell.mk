override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override PARSERDIR	:= parsing/
override LEXERDIR	:= lexer/
override EXECDIR	:= exec/
override BUILTINDIR := env/
override SIGNALDIR	:= signal/


SRC += $(addprefix $(MAINDIR), $(addsuffix .c, $(MAIN)))

override MAIN := \
	main \


SRC += $(addprefix $(PARSERDIR), $(addsuffix .c, $(PARSERSRC)))

override PARSERSRC := \
	parser \
	process_commands \
	commands_gestionary \
	free_commands \


SRC += $(addprefix $(LEXERDIR), $(addsuffix .c, $(LEXERSRC)))

override LEXERSRC := \
	lexer \
	process_token \
	token_gestionary \
	token_utils \
	free_token \

SRC += $(addprefix $(SIGNALDIR), $(addsuffix .c, $(SIGNALSRC)))

override SIGNALSRC := \
	signal \

SRC += $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

override EXECSRC := \
	exec \
	redirections \

# SRC += $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))

# override BUILTINSRC := \
# 	cd \
# 	echo \
# 	env \
# 	exit \
# 	export \
# 	pwd \
# 	unset \


# SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

# override ENVSRC := \
# 	env \
