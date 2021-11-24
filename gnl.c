/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:37:59 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/24 04:13:55 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include <stdio.h>


void	clean_buffer(t_buf *reader)
{
	int	i;

	i = 0;
	while (i < reader->memo)
	{
		reader->buffer[i] = 0;
		i++;
	}
}

void	check_eol(int fd, t_count *count, t_buf *reader, t_list **lst)
{
	if (reader->memo < BUFFER_SIZE && reader->buffer[reader->memo] == '\n')
	{
		ft_lstadd_back(lst, ft_lstnnew(reader->buffer, reader->begin, reader->memo));
		count->end = 1;
		//printf("\nfin de ligne. memo = %d, begin = %d, buffer = -->%s<--\n", reader->memo, reader->begin, reader->buffer);
		reader->begin = reader->memo + 1;
		reader->memo++;
		//clean_buffer(reader);
		//begin et memo se trouvent donc juste apres le \n
		//clean_buffer(buffer, count->buffer + 1, BUFFER_SIZE);
	}
	else if (((reader->memo < BUFFER_SIZE) && !(reader->buffer[reader->memo]))
		|| (reader->memo == BUFFER_SIZE))
	{
		ft_lstadd_back(lst, ft_lstnnew(reader->buffer, reader->begin, reader->memo));
		//clean_buffer(buffer, BUFFER_SIZE, BUFFER_SIZE);
		//printf("\nfin de BUFFER. memo = %d, begin = %d, buffer = -->%s<--\n", reader->memo, reader->begin, reader->buffer);
		clean_buffer(reader);
		if (!read(fd, reader->buffer, BUFFER_SIZE))
			count->end = 1;
		reader->memo = 0;
		reader->begin = 0;
	}
}

char	*ft_makeline(t_list *lst, int n)
{
	size_t	i;
	char	*dest;
	t_list	*cursor;
	size_t	j;
	char	*cpy;

	dest = (char *) malloc((((ft_lstsize(lst) - 1) * BUFFER_SIZE) + n + 2));
	if (!dest)
		return (NULL);
	i = 0;
	cursor = lst;
	j = 0;
	while (cursor)
	{
		j = 0;
		cpy = cursor->content;
		while (cpy[j])
			dest[i++] = cpy[j++];
		cursor = cursor->next;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static t_buf	reader = {.buffer = "", .memo = 0, .begin = 0};
	char		*dest;
	t_count		count;
	t_list		*lst;

	count.end = 0;

	free(NULL);

	if (!(reader.buffer[0]) && !(read(fd, reader.buffer, BUFFER_SIZE)))
		return (NULL);


//	if (!reader.buffer[0])
//		if (!read(fd, reader.buffer, BUFFER_SIZE))
//			return (NULL);

//	printf("\nEntree de fonction, buffer = \"%s\"\n", reader.buffer);

	lst = NULL;
	while (!count.end)
	{
		while (reader.memo < BUFFER_SIZE
			&& reader.buffer[reader.memo] && reader.buffer[reader.memo] != '\n')
			reader.memo++;
		check_eol(fd, &count, &reader, &lst);
	}
	dest = ft_makeline(lst, reader.memo);
	ft_lstclear(&lst, &free);
	if (!dest || !(*dest)){
		free(dest);
		return (NULL);}
//	ft_lstclear(&lst, &free);
	return (dest);
}
