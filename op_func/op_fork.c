/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:50:03 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 15:50:05 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

static void	t_processes_add_to_start(t_processes **proc_start,
										t_processes **proc_end, t_processes *new_obj)
{
	new_obj->next = *proc_start;
	new_obj->prev = NULL;
	if (*proc_start)
		(*proc_start)->prev = new_obj;
	else
		*proc_end = new_obj;
	*proc_start = new_obj;
}

void		copy_prcs(t_processes **proc_start, t_processes **proc_end,
							 t_processes *copy, int pc)
{
	int			i;
	t_processes	*new_obj;

	g_cw.proc_counter++;
	if (!(new_obj = (t_processes *)malloc(sizeof(t_processes))))
		cw_perror_exit(ERR_MALLOC_MESSAGE, MALLOC);
	new_obj->pc = pc;
	new_obj->carry = copy->carry;
	i = -1;
	while (++i < REG_NUMBER)
		new_obj->registers[i] = copy->registers[i];
	new_obj->is_alive = copy->is_alive;
	new_obj->champ_number = copy->champ_number;
	new_obj->cmd = 0;
	new_obj->exec_cycles = -1;
	new_obj->color = copy->color;
	g_cw.mp.color_map_pc[pc]++;
	t_processes_add_to_start(proc_start, proc_end, new_obj);
}

void	op_fork(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;

	pos = (op.args[0].value % IDX_MOD) + pr->cur_pos;
}
