/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:21:52 by tarini            #+#    #+#             */
/*   Updated: 2025/06/15 11:15:36 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# include <unistd.h>
# include <stdarg.h>

# define UP_HEXA "0123456789ABCDEF"
# define LOW_HEXA "0123456789abcdef"
# define DECIMAL "0123456789"

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

// libft and other function

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
char			*ft_strdup(const char *src);
void			*ft_calloc(size_t elementCount, size_t elementSize);
unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
char			*ft_strchr(const char *str, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *str, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			**ft_split(const char *str, char sep);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
void			ft_putchar_fd(char s, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// bonus

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

// printf

int				ft_printf(const char *format, ...);
int				ft_putchar(char c);
int				ft_putstr(char *str);
int				ft_putnbrbase(long n, const char *base, int signed_flag);
int				handle_conversion(const char format, va_list args);

// printfd ldev
int	ft_printfd(const char *str, ...);
int	ft_printfd_cases(va_list ptr, int i, const char *str, int *ptr_return_value);
void	ft_printd_hex(va_list ptr, int i, const char *str,
	int *ptr_return_value);
void	ft_printfd_pointer(va_list ptr, int *ptr_return_value);
void	ft_printfd_char(va_list ptr, int i, const char *str,
	int *ptr_return_value);
void	ft_printfd_num(va_list ptr, int i, const char *str,
		int *ptr_return_value);
char	*ft_utoa(unsigned int n);
// static char	*count_for_malloc(long *integer, int *is_negative);
// static char	*convert(long n, int i, char *result, char *buff);
char	*ft_itoa_hexx(unsigned long nbr);
char	*zero_case(void);
unsigned long	calculate_length(unsigned long nbr);
char	*ft_strtoupper(char *convert);


// other function

int				ft_strcmp(const char *s1, const char *s2);
t_bool			ft_atoi_only_num(const char *str, int *result);
double			ft_atod(const char *str);
int				ft_pass(int i, const char *str, int *s);
double			ft_atof(const char *str);
void			*ft_realloc(void *ptr,size_t old_size, size_t new_size);

#endif