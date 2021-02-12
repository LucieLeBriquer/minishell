/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftfull.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:08:59 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/11 17:57:17 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTFULL_H
# define LIBFTFULL_H
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4095
# endif

/*
** libft
*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void		*ft_memset(void *s, int c, size_t n);
void		*ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_issep(char c, const char *charset);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strnstr(const char *big, const char *little, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strdup(const char *s);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
char		*ft_utoa(unsigned int n);
char		*ft_utox(unsigned int n);
char		*ft_utoxx(unsigned int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar(char c);
void		ft_putstr(char *s);
void		ft_putendl(char *s);
void		ft_putnbr(int n);
char		**ft_splitchar(const char *s, char c);
char		**ft_split(const char *s, const char *set);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(const char *s, unsigned int start, size_t len);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)());
int			ft_issep(char c, const char *charset);
int			ft_isspace(char c);
int			ft_max(int a, int b);
int			ft_min(int a, int b);

/*
** get_next_line
*/

typedef struct s_buffer
{
	int		size;
	char	content[BUFFER_SIZE + 1];
}			t_buffer;

char		*join_and_realloc(char *s, char *buf, size_t size);
int			find_char_index(char *str, char c);
int			get_next_line(int fd, char **line);

/*
** ft_printf
*/

typedef struct s_print
{
	int		align;
	int		zero;
	int		field;
	int		precision;
	int		type;
	int		fd;
}			t_print;

typedef int	(*t_func)(t_print, va_list);

int			size_int(t_print param, char *nb_itoa);
int			size_ptr(unsigned long ptr, int prec);
char		*ft_utoct(unsigned int n);
char		*ft_ptoa(unsigned long ptr, int size);
void		init_param(t_print *param);
void		print_param_useful(t_print p);
int			is_type(char c);
const char	*parse_param(t_print *param, const char *str, va_list args);
int			is_all_coherent(const char *str);
const char	*print_str_classic(const char *str, int *nb_char, int fd);
void		print_param(t_print p, va_list args, int *nb_char);
int			ft_printf(const char *str, ...);
int			ft_printf_fd(int fd, const char *str, ...);
void		fill_str_s(char **to_print, char *str, t_print param, int size);
void		fill_int_right_p(char **to_print, char *nb, t_print par, int size);
void		fill_int_right(char **to_print, char *nb, int size);
void		fill_int_left_p(char **to_print, char *nb, t_print par, int size);
void		fill_int_left(char **to_print, char *nb, int size);
void		fill_int_zero(char **to_print, char *nb, int size);
void		fill_int_easy(char **to_print, char *nb, int size);
void		fill_int(char **to_print, char *nb, t_print param, int size);
int			print_0chr(t_print param, va_list args);
int			print_1str(t_print param, va_list args);
int			print_2ptr(t_print param, va_list args);
int			print_3dbl(t_print param, va_list args);
int			print_4int(t_print param, va_list args);
int			print_5uns(t_print param, va_list args);
int			print_6hex(t_print param, va_list args);
int			print_7hxx(t_print param, va_list args);
int			print_8pct(t_print param, va_list args);
int			print_9oct(t_print param, va_list args);
int			min_not_neg(int a, int b);

#endif
