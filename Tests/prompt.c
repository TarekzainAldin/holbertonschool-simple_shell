#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main(void)
{
	char *buffer = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
	printf("$ ");
	nread = getline(&buffer, &len, stdin);

	if (nread == -1)
	{
		printf("Error reading input.\n");
	break;
	}
	else if (nread == 1)
	{
	printf("End of file reached. Exiting...\n");
	break;
	}
	else if (strcmp(buffer, "EOD\n") == 0)
	{

	/* Vérifie si l'entrée t EOD
	 *
	 *
	 */
	printf("Exiting...\n");
	break;
	}
	else
	{
	printf("%s", buffer);
	}
	}
	free(buffer);

	/*Libération de la mémoire allouée par g
	 *
	 */
	return (0);
}
