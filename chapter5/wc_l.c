#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_wc_l(const int fd);


int main(int argc, char *argv[])
{
	if (argc == 1) {
		do_wc_l(STDIN_FILENO);
	} else {
		int i;

		for (i = 1; i < argc; i++) {
			int fd;

			fd = open(argv[i], O_RDONLY);
			if (!fd) {
				perror(argv[i]);
				exit(1);
			}
			do_wc_l(fd);
			close(fd);
		}
	}
	exit(1);
}


static void do_wc_l(const int fd)
{
	unsigned long n = 0;
	char c[1];
	char prev = '\n';

	while (read(fd, c, sizeof c) != '\0') {
		if (*c == '\n') {
			n++;
		}
		prev = *c;
	}
	if (prev != '\n') {
		n++;
	}
	printf("line: %ld\n", n);
}
