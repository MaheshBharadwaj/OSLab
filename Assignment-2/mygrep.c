#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{

	int source_d;

	char line[100];

	char *pattern;

	char buffer;
	int counter = 0;

	if (argc == 3)
	{
		pattern = argv[1];

		source_d = open(argv[2], O_RDONLY);

		if (source_d == -1)
		{
			fprintf(stderr, "No such file");
			return 1;
		}

		while (read(source_d, &buffer, 1))
		{
			if (buffer == '\n')
			{
				line[counter] = '\0';
				if (strstr(line, pattern))
					printf("%s\n", line);
				counter = 0;
				for (int i = 0; i < 100; i++)
					line[i] = 0;
			}
			else
				line[counter++] = buffer;
		}
		return 0;
	}

	if (argc == 4)
	{
		pattern = argv[2];

		source_d  = open(argv[3], O_RDONLY);

		if (source_d == -1)
		{
			fprintf(stderr, "No such file");
			return 1;
		}

		if (strcmp(argv[1], "-c") == 0)
		{
			int matches = 0;
			while (read(source_d, &buffer, 1))
			{
				if (buffer == '\n')
				{
					line[counter] = '\0';
					if (strstr(line, pattern))
						matches++;
					counter = 0;
					for (int i = 0; i < 100; i++)
						line[i] = 0;
				}
				else
					line[counter++] = buffer;
			}
			printf("No of matches: %d\n", matches);
		}
		else if (strcmp(argv[1], "-h") == 0)
		{

			while (read(source_d, &buffer, 1))
			{
				if (buffer == '\n')
				{
					line[counter] = '\0';
					if (strstr(line, pattern))
						printf("%s: %s\n", argv[3], line);
					counter = 0;
					for (int i = 0; i < 100; i++)
						line[i] = 0;
				}
				else
					line[counter++] = buffer;
			}
		}
		else if (strcmp(argv[1],"-v") == 0)
		{

			while (read(source_d, &buffer, 1))
			{
				if (buffer == '\n')
				{
					line[counter] = '\0';
					if (!strstr(line, pattern))
						printf("%s\n",line);
					counter = 0;
					for (int i = 0; i < 100; i++)
						line[i] = 0;
				}
				else
					line[counter++] = buffer;
			}
		}
		else
		{
			fprintf(stderr, "No Such argument!\n");
			return 1;
		}
	}
	close(source_d);
}
