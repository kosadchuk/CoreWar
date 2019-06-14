#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdlib.h>

extern t_err_manager_storage g_on_error;

void	fail_to_open_file()
{
	ft_memdel((void **)&g_on_error.file_name);
	ft_putendl("Error: failed to open the file.");
	ft_putendl("Probably you have not enough rights, or file doesn't exist.");
	exit(3);
}

void	missed_new_line()
{
	ft_memdel((void **)&g_on_error.file_name);
	ft_memdel((void **)&g_on_error.file_content);
	ft_putendl("missed new line at the end of file");
	exit(4);
}
