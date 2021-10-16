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

void	check_end_of_line(int fd, int *i, char *buffer, char *dest)
{
	if (i[1] < BUFFER_SIZE && buffer[i[1]] == '\n')
	{
		dest[i[0]] = '\n';
		(1 + i[0])[dest] = 0;
		i[2] = 1;
		clean_buffer(buffer, i[1] + 1, BUFFER_SIZE);
	}
	else if (((i[1] < BUFFER_SIZE) && !(buffer[i[1]])) || (i[1] == BUFFER_SIZE))
	{
		clean_buffer(buffer, BUFFER_SIZE, BUFFER_SIZE);
		if (!read(fd, buffer, BUFFER_SIZE))
		{
			dest[i[0]] = 0;
			i[2] = 1;
		}
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*dest;
	char		end;
	int			i[3];

	i[2] = 0;
	if (!(buffer[0]) && !(read(fd, buffer, BUFFER_SIZE)))
		return (NULL);
	dest = NULL;
	i[0] = 0;
	while (!i[2])
	{
		i[1] = 0;
		dest = ft_realloc(dest, i[0]);
		if (!dest)
			return (0);
		while (i[1] < BUFFER_SIZE && buffer[i[1]] && buffer[i[1]] != '\n')
			dest[i[0]++] = buffer[i[1]++];
		check_end_of_line(fd, i, buffer, dest);
	}
	return (dest);
}
