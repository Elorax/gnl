/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:38:10 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/23 22:12:51 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

typedef struct s_count
{
	char	end;
}	t_count;

typedef struct {
	char	buffer[BUFFER_SIZE];
	int		memo;
	int		begin;
} t_buf;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	*ft_strndup(char const *s, int begin, int end);
t_list	*ft_lstnnew(void *s, int begin, int end);
void	ft_lstadd_back(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_char_swap(char *a, char *b);
void	clean_buffer(t_buf *reader);
void	check_eol(int fd, t_count *count, t_buf *reader, t_list **lst);
char	*ft_makeline(t_list *lst, int n);
char	*get_next_line(int fd);

#endif
