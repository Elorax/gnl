#include <stdio.h>
#include <stdlib.h>


int main()
{
	char	*dest;

	dest = (char *) malloc(19);
	/*dest[0] = 'H';
	dest[1] = 'e';
	dest[2] = 'l';
	(dest + 3) = "lo\n";
	dest[7] = '?';
	dest[8] = 0;*/
	= "Hello\n";
	printf("%s", dest);
}
