/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:18:15 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/20 17:04:46 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>
# include <bits/types.h>
# include <limits.h>
# define BASE_DEC "0123456789"
# define BASE_HEX_LO "0123456789abcdef"
# define BASE_HEX_UP "0123456789ABCDEF"
# define VAR_SPECIFIERS "cspdiuxX%"
# define BUFFER_SIZE 100

typedef enum e_bool
{
	f,
	t
}	t_bool;

// POINTER TABLE STRUCTS
typedef struct s_ptr_tab
{
	size_t	size;
	ssize_t	count;
	void	*orig;
	void	*read;
	void	**start;
	void	**end;
}	t_ptr_tab;

// LINKED LIST STRUCTS
typedef struct s_node
{
	void			*content;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	ssize_t				count;
	ssize_t				data_size;
	t_node				*head;
	t_node				*tail;
}	t_list;

// ARRAY
size_t		ft_arrlen(void **ptr);

// CHAR
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

// LIST
//t_list	*arr_to_list(t_list **lst, void *arr);
size_t		ft_lstsize(t_list *lst);
ssize_t		ft_lstfind_index(t_list *list, t_node *node_to_find);
t_list		*ft_lstcpy(t_list *list);
t_list		*ft_lstmap(t_list *list, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstdel_list(t_list *list, void (*del)(void *));
t_list		*ft_lstnew_list(ssize_t data_size);
t_node		*ft_lstfind_content_int(t_list *list, t_node *offset, void *data);
t_node		*ft_lstfind_node(t_list *list, ssize_t index);
t_node		*ft_lstlast(t_list *list);
t_node		*ft_lstnew_node(ssize_t data_size, void *content);
void		ft_lstadd_back(t_list *list, t_node *new_node);
void		ft_lstadd_front(t_list *list, t_node *new_node);
void		ft_lstadd_insert_pos(t_list *list, t_node *new_node, ssize_t pos);
void		ft_lstadd_insert(t_list *list, t_node *new_node, t_node *node);
void		ft_lstdel_between(t_list *list, t_node *node, void (*del)(void *));
void		ft_lstdel_first(t_list *list, void (*del)(void *));
void		ft_lstdel_last(t_list *list, void (*del)(void *));
void		ft_lstdel_pos(t_list *list, void (*del)(void *), ssize_t pos);
void		ft_lstdel_wrapper(t_list *list, t_node *node, void (*del)(void *));
void		*ft_lstget_data_index(t_list *list, ssize_t index);
void		*ft_lstget_data_node(t_node *node);
void		ft_lstiter(t_list *list, void (*f)(void *));
void		ft_lstswap_right(t_list *list, t_node *node);
void		ft_lstswap_left(t_list *list, t_node *node);
void		ft_lstswap_ends(t_list *list);

// MEMORY
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_stcmp(const void *s1, const void *s2);
ssize_t		ft_sstcmp(const void *s1, const void *s2);
ssize_t		ft_tabfind(void *ptr, t_ptr_tab tab, t_bool inclusive);
t_ptr_tab	*ft_taballoc(t_ptr_tab *ptr_tab, char *orig, size_t size);
t_ptr_tab	*ft_tabfree(t_ptr_tab **ptr_tab, t_bool free_table);
t_bool		ft_tabcmp(t_ptr_tab *tab1, t_ptr_tab *tab2, size_t t1i, size_t t2i);
void		**ft_freematrix(void **matrix);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_tabdelone(t_bool start_or_end, ssize_t i, t_ptr_tab *tab);
void		*ft_tabdelboth(ssize_t i, t_ptr_tab *tab);
void		ft_bzero(void *s, size_t n);

// NUMBER
double		ft_atof(const char *str);
float		ft_pow_float(float base, float exp);
int			ft_abs(int n);
int			ft_atoi(const char *str);
int			ft_max(int a, int b);
int			ft_min(int a, int b);
int			ft_pow_int(int base, int exp);
void		*ft_intset(void *b, int c, size_t len);

// PRINT
int			ft_printf(int fd, const char *fmt, ...);
size_t		ft_putchar_fd(char c, int fd);
size_t		ft_putendl_fd(char *s, int fd);
size_t		ft_putnbr_fd(int n, int fd, char *base, t_bool sign);
size_t		ft_putstr_fd(char *s, int fd);
t_bool		check_specifiers(const char *s);
void		ft_perror(char *msg, char *err, t_bool must_exit, int exit_code);

// READ
char		*append_buffer_to_line(char *line,
				char *remaining_chars, size_t len);
char		*get_next_line(int fd);
char		*read_into_buffer(int fd, char *remaining_chars);
ssize_t		found_newline(char *remaining_chars);
t_bool		set_line(char **line, char *remaining_chars);

// STRING
char		**ft_split(const char *s, char c);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strlast(char *s);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_strndup(const char *s, size_t n);
char		*ft_strnchr(const char *s, int c, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_substr(const char *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

#endif
