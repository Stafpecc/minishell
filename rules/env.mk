override ENVDIR := src/env/

SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC := \
	env \
