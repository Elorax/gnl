#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "gnl.h"

int main(int argc, char **argv)
{
	int	fichier;
	char	*s1;
	
	if (argc > 1)
		fichier = open(argv[1], O_RDONLY);
	else
		fichier = open("test.txt", O_RDONLY);
	if (fichier == -1)
 	{
		printf("Erreur lors de l'ouverture du fichier");
		return (0);
	}

	int i = 0;
	while ((s1 = get_next_line(fichier)))
		{printf("%s", s1);
		free(s1);
		i++;}
//	printf("==>%d<==", i);
/*
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);
	s1 = get_next_line(fichier);
		printf("%s", s1);*/
	free(s1);
	close(fichier);
	return (0);
}
