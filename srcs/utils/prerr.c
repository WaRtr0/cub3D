#include <unistd.h>

void	prerr(char *msg)
{
	while (*msg)
		write(2, msg++, 1);
}
