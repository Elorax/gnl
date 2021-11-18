#include "get_next_line.h"

void	ft_char_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	clean_buffer(char *buffer, int nb, int size)
{
	int	i;

	i = 0;
	/*if (nb >= size)
	{
		ft_memset(buffer, 0, BUFFER_SIZE);
		return ;
	}*/
	while (i < nb)
		buffer[i++] = 0;
	i = -1;
	while (++i + nb < size)
		ft_char_swap(buffer + i, buffer + nb + i);
}

void	check_eol(int fd, t_count *count, char *buffer, t_list **lst)
{
	if (count->buffer < BUFFER_SIZE && buffer[count->buffer] == '\n')
	{
		ft_lstadd_back(lst, ft_lstnnew(buffer, count->buffer + 1));
		count->end = 1;
		clean_buffer(buffer, count->buffer + 1, BUFFER_SIZE);
	}
	else if (((count->buffer < BUFFER_SIZE ) && !(buffer[count->buffer]))
			|| (count->buffer == BUFFER_SIZE))
	{
		ft_lstadd_back(lst, ft_lstnnew(buffer, count->buffer));
		clean_buffer(buffer, BUFFER_SIZE, BUFFER_SIZE);
		if (!read(fd, buffer, BUFFER_SIZE))
			count->end = 1;
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
	//dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = "";
	char	*dest;
	t_count	count;
	t_list	*lst;

	count.end = 0;
	if (!(buffer[0]) && !(read(fd, buffer, BUFFER_SIZE)))
		return (NULL);
	count.dest = 0;
	lst = NULL;
	while (!count.end)
	{
		count.buffer = 0;
		while (count.buffer < BUFFER_SIZE
			&& buffer[count.buffer] && buffer[count.buffer] != '\n')
			count.buffer++;
		check_eol(fd, &count, buffer, &lst);
	}
	dest = ft_makeline(lst, count.buffer);
	if (!dest)
		return (NULL);
	ft_lstclear(&lst, &free);
	return (dest);
}
