override EXECDIR := src/libft/

SRC += $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

override EXECSRC := \
	ft_isdigit \
	ft_isalpha \
	ft_isalnum \
	ft_isascii \
	ft_isprint \
	ft_strlen \
	ft_memset \
	ft_bzero \
	ft_memcpy \
	ft_memmove \
	ft_strlcpy \
	ft_strlcat \
	ft_toupper \
	ft_tolower \
	ft_strchr \
	ft_strrchr \
	ft_strncmp \
	ft_memchr \
	ft_memcmp \
	ft_strnstr \
	ft_atoi \
	ft_strdup \
	ft_calloc \
	ft_split \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_itoa \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd \
	ft_strmapi \
	ft_striteri
	ft_lstnew_bonus \
	ft_lstadd_front_bonus \
	ft_lstsize_bonus \
	ft_lstlast_bonus \
	ft_lstadd_back_bonus \
	ft_lstdelone_bonus \
	ft_lstclear_bonus \
	ft_lstiter_bonus \
	ft_lstmap_bonus \
