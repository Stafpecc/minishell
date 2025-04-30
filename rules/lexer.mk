override LEXERDIR := src/lexer/

SRC += $(addprefix $(LEXERDIR), $(addsuffix .c, $(LEXERSRC)))

override LEXERSRC := \
	lexer \
