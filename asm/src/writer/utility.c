#include <stdio.h>

void		int_to_bytecode(char *data, int value, int bytes)
{
	int		i;

	i = 0;
	while (bytes)
	{
		data[bytes - 1] = (char)((value >> i) & 0xFF);
		printf("c = [%c]\n", (char)((value >> i) & 0xFF));
		i += 8;
		bytes--;
	}
}
