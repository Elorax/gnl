#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int	fichier;
	char	*s1;
	
	if (argc > 1)
		fichier = open(argv[1], O_RDONLY);
	else
		fichier = open("random500.txt", O_RDONLY);
	if (fichier == -1)
 	{
		printf("Erreur lors de l'ouverture du fichier");
		return (0);
	}
	while ((s1 = get_next_line(fichier)))
	{
		printf("%s", s1);
		free(s1);
	}
	close(fichier);
	return (0);
}
