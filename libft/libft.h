/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:08:50 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/09 18:05:52 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putstr(char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strchr(const char *s, int c);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *s);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
char				*ft_strcpy(char *dest, const char *src);
/*printf*/
int					ft_printstr_fd(char *s, int fd);
int					ft_printchar_fd(char c, int fd);
int					ft_printnbr_fd(int nbr, int fd);
void				ft_puthex_fd(unsigned long n, int fd, char *base_to);
int					get_strlen_for_int(unsigned long n, char *base);
int					ft_printhex_adress(unsigned long n, int fd, char *base_to);
int					ft_printhex(unsigned int n, int fd, char *base_to);
int					check_format(char c, va_list ptr);
int					ft_printf(const char *speci, ...);
void				ft_putnbr_unsigned_fd(unsigned int n, int fd);
int					ft_printnbr_unsigned_fd(unsigned int nbr, int fd);
/*get_next_line*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

char				*get_next_line(int fd);
void				readline(int fd, char **save);
char				*before_line_break(char *buf);
char				*after_line_beak(char *buf);
char				*ft_strdup_line(const char *s);
int					include_newline(char *s);
void				ft_free(char **s1, char **s2, char **s3);

#endif