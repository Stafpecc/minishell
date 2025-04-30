override BUILTINDIR := src/builtin/

SRC += $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))

override BUILTINSRC := \
	cd \
	echo \
	env \
	exit \
	export \
	pwd \
	unset \
