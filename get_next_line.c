#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
 #define BUFFER_SIZE 64
#endif

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	int	size;
	char	*dest;
	int	i;
	int	j;

	size = ft_strlen(s1) + n;
	dest = malloc(sizeof(char) * (size + 1));

	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] && j < n)
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = 0;
	return (dest);

}

char	*get_next_line(int fd)
{
	size_t	ret_read;
	char	*buffer;
	size_t	i;
	char	*dest;
	char	end_of_line;

	end_of_line = 0;
	buffer = malloc(BUFFER_SIZE);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[i] = 0;
		i++;
	}
	ret_read = 1;
	int	j = 0;
	while (!end_of_line && ret_read != 0)
	{
		ret_read = read(fd, buffer, BUFFER_SIZE);
		j++;
		i = 0;
		while (buffer[i] != '\n' && i < ret_read)
			i++;
		if (i < ret_read)				//'\n' trouve. Attention si \n trouve au dernier caractere. A CORRIGER.
		{
			dest = ft_strnjoin(dest, buffer, i + 1);//Alloue une chaine de la taille de dest + i + 2, concatene dest et buffer, termine par zero.
			printf("LIGNE FINIE APRES %d ITERATIONS\n\n\n", j);
			end_of_line = 1;
		}
		else
		{
			dest = ft_strnjoin(dest, buffer, i + 1);
		}
	}
	return (dest);
}

int main()
{
	int	fichier;

	fichier = open("test.txt", O_RDONLY);
	printf("-->%s<--", get_next_line(fichier));
	close(fichier);
}
