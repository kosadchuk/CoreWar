#include "../../libft/inc/libft.h"

#include <stdlib.h>

void	not_enough_args()
{
	ft_putendl("Error: not enough arguments.");
	ft_putendl("usage: ./asm file.cor");
	exit(1);
}

void	wrong_file_extension()
{
	ft_putendl("Error: file must have a name with "
				"at least 1 character and .cor extension");
	exit(2);
}
