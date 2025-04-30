override EXECDIR := src/exec/

SRC += $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

override EXECSRC := \
	exec \
	redirections \
