# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define MEGA 1000000

typedef unsigned char BYTE;

int main(int argc, char* argv[]) {
	if (argc < 2 || argc > 3) {
		fprintf(stderr, "invalid command-line arguments\n");
		exit(1);
	}

	int i, len = atoi(argv[1]);
	// In modern Linux, maximum stack size is typically 8MB 
	if (len >= 8) {
		fprintf(stderr, "Exceeds maximum stack size\n");
		exit(1);
	}

	len *= MEGA;
	BYTE array[len];
	for (i = 0; i < len; i++)
		array[i]++;

	if (argc == 2)	{
		while(1) { continue; }
	}
	else 	sleep(atoi(argv[2]));

	return 0;
}

