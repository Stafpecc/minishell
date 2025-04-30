override MAINDIR := src/

SRC += $(addprefix $(MAINDIR), $(addsuffix .c, $(MAIN)))

override MAIN := \
	main \
