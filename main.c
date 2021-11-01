#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd);

int main()
{
	int	fichier;
	//char	*test = ":)";
	fichier = open("test.txt", O_RDONLY);
	char	*s1 = get_next_line(fichier);	

	char	*s2 = get_next_line(fichier);	
	char	*s3 = get_next_line(fichier);	
	char	*s4 = get_next_line(fichier);	
	char	*s5 = get_next_line(fichier);	
	char	*s6 = get_next_line(fichier);
	printf("%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6);
	close(fichier);
	free(s1);
	free(s2);
	free(s3);
	free(s4);
	free(s5);
	free(s6);
}
