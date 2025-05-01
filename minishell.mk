override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override PARSERDIR	:= src/parsing/
override LEXERDIR	:= src/lexer/
override EXECDIR	:= src/exec/
override BUILTINDIR := src/builtin/
override ENVDIR		:= src/env/


SRC += $(addprefix $(MAINDIR), $(addsuffix .c, $(MAIN)))

override MAIN := \
	main \


# SRC += $(addprefix $(PARSERDIR), $(addsuffix .c, $(PARSERSRC)))

# override PARSERSRC := \
# 	parsing \


# SRC += $(addprefix $(LEXERDIR), $(addsuffix .c, $(LEXERSRC)))

# override LEXERSRC := \
# 	lexer \



# SRC += $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

# override EXECSRC := \
# 	exec \
# 	redirections \


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
