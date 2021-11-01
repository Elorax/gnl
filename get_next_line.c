#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	while (i < nb)
		buffer[i++] = 0;
	i = -1;
	while (++i + nb < size)
		ft_char_swap(buffer + i, buffer + nb + i);
}

char	*ft_realloc(char *str, size_t size)
{
	char	*tmp;
	int		i;

	tmp = (char *) malloc(sizeof(char) * (size + BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tmp[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	return (tmp);
}

void	check_end_of_line(int fd, t_count *count, char *buffer, char *dest)
{
	if (count->buffer < BUFFER_SIZE && buffer[count->buffer] == '\n')
	{
		dest[count->dest] = '\n';
		(1 + count->dest)[dest] = 0;
		count->end = 1;
		clean_buffer(buffer, count->buffer + 1, BUFFER_SIZE);
	}
	else if (((count->buffer < BUFFER_SIZE) && !(buffer[count->buffer]))
		|| (count->buffer == BUFFER_SIZE))
	{
		clean_buffer(buffer, BUFFER_SIZE, BUFFER_SIZE);
		if (!read(fd, buffer, BUFFER_SIZE))
		{
			dest[count->dest] = 0;
			count->end = 1;
		}
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*dest;
	t_count		count;

	count.end = 0;
	if (!(buffer[0]) && !(read(fd, buffer, BUFFER_SIZE)))
		return (NULL);
	dest = NULL;
	count.dest = 0;
	while (count.end == 0)
	{
		count.buffer = 0;
		dest = ft_realloc(dest, count.dest);
		if (!dest)
			return (NULL);
		while (count.buffer < BUFFER_SIZE && buffer[count.buffer]
			&& buffer[count.buffer] != '\n')
			dest[(count.dest)++] = buffer[(count.buffer)++];
		check_end_of_line(fd, &count, buffer, dest);
	}
	return (dest);
}
