#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const int fd);

int main(int argc, char *argv[])
{
        int i;

	if (argc == 1) {
		do_cat(STDIN_FILENO);
	}
	else {
        	for (i = 1; i < argc; i++) {
                	int fd;

			fd = open(argv[i], O_RDONLY);
			if (!fd) {
				perror(argv[i]);
				exit(1);
			}
			do_cat(fd);
			close(fd);
		}
        }
        exit(0);
}


#define BUFFER_SIZE 2048

static void do_cat(const int fd)
{
        unsigned char buf[BUFFER_SIZE];
        int n;

        for (;;) {
                n = read(fd, buf, sizeof buf);
                if (n == 0) break;
                write(STDOUT_FILENO, buf, n);
        }
}

