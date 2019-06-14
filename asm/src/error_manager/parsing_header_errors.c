#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdlib.h>

extern t_err_manager_storage g_on_error;

void				wrong_header_in_file(int type)
{
	if (type == 1)
		ft_putendl("Error: duplicate .name or .comment file");
	if (type == 2)
		ft_putendl("Error: .name or .commend without the value");
	if (type == 3)
		ft_putendl("Error: smth went wrong while header parsing");
	else
	{
		ft_putstr("Error: is seems like there is a faggot in front of monitor: ");
		ft_putnbr(type);
		ft_putendl("");
	}
	ft_memdel((void **)&g_on_error.file_name);
	ft_memdel((void **)&g_on_error.file_content);
	ft_memdel((void **)&(g_on_error.to_del->name));
	ft_memdel((void **)&(g_on_error.to_del->comment));
	exit(5);
}
