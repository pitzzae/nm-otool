#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	int			fd;
	char		*buf[2048];

	if (ac < 2)
		return (0);
	else
	{
		fd = open(av[1], O_RDONLY);
		while (read(fd, buf[0], 1))
			;
		printf("%s\n", buf[0]);
	}
}