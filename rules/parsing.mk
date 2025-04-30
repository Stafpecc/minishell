override PARSERDIR := src/parsing/

SRC += $(addprefix $(PARSERDIR), $(addsuffix .c, $(PARSERSRC)))

override PARSERSRC := \
	parsing \
