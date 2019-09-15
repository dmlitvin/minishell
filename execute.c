/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:28:23 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/15 15:28:35 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char
*g_built_in_list[] = {"echo", "cd", "env", "setenv", "unsetenv", "exit"};
void			(*g_built_in_func_list[])
		(t_minishell*) = {echo, cd, env, set_env, unset_env, exit_shell};

static void	find_run_executable(t_minishell *shell_info)
{
	(void)shell_info;
}

void		execute_command(t_minishell *shell_info)
{
	size_t			i;
	const size_t	built_in_count = sizeof(g_built_in_list) / sizeof(char*);

	if (!shell_info->av[0])
		return ;
	i = 0;
	while (i < built_in_count)
	{
		if (ft_strequ(shell_info->av[0], g_built_in_list[i]))
		{
			g_built_in_func_list[i](shell_info);
			return ;
		}
		i++;
	}
	find_run_executable(shell_info);
}
