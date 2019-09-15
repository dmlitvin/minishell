/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:18:27 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/15 16:18:33 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_minishell *shell_info)
{
	if (shell_info->av[1] && shell_info->av[2] && !shell_info->av[3])
	{
		ft_lstadd_end(&shell_info->env_list,
				make_variable(shell_info->av[1], shell_info->av[2]));
		shell_info->last_exit_code = 0;
	}
	else
	{
		ft_putendl_fd("usage: setenv key value", 2);
		shell_info->last_exit_code = 1;
	}
}

void	env(t_minishell *shell_info)
{
	t_variable	*variable;
	t_list		*list;

	list = shell_info->env_list;
	while (list)
	{
		variable = list->content;
		ft_printf("%s=%s\n", variable->key, variable->value);
		list = list->next;
	}
	shell_info->last_exit_code = 0;
}

void	unset_env(t_minishell *shell_info)
{
	if (shell_info->av[1] && !shell_info->av[2])
	{
		shell_info->last_exit_code = 0;
		delete_env(shell_info->av[1], shell_info);
		if (shell_info->last_exit_code)
		{
			ft_putstr_fd(shell_info->av[1], 2);
			ft_putendl_fd(": no such variable", 2);
		}
	}
	else
	{
		ft_putendl_fd("usage: unsetenv key", 2);
		shell_info->last_exit_code = 1;
	}
}
