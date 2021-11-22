/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:38:05 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 17:38:06 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_strndup(char const *s, int n)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *) malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

t_list	*ft_lstnnew(void *s, int n)
{
	t_list	*l;
	char	*cpy;

	l = (t_list *) malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	cpy = (char *) s;
	l->content = ft_strndup((char *)s, n);
	if (!(l->content))
	{
		free(l);
		return (NULL);
	}
	l->next = NULL;
	return (l);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cursor;

	if (alst && *alst)
	{
		cursor = *alst;
		while (cursor->next)
		{
			cursor = cursor->next;
		}
		cursor->next = new;
	}
	else if (alst)
		*alst = new;
}

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*cursor;

	i = 0;
	cursor = lst;
	while (cursor)
	{
		cursor = cursor->next;
		i++;
	}
	return (i);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!del || !lst ||!(*lst))
		return ;
	temp = *lst;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}
