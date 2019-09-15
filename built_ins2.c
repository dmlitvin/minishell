/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:18:35 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/15 16:18:41 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_minishell *shell_info)
{
	char	**av;

	if (shell_info->av[1])
		ft_putstr(shell_info->av[1]);
	av = shell_info->av[1] ? shell_info->av + 2 : shell_info->av + 1;
	while (*av)
		ft_printf(" %s", *av++);
	ft_putchar('\n');
	shell_info->last_exit_code = 0;
}

void	cd(t_minishell *shell_info)
{
	(void)shell_info;
}

void	exit_shell(t_minishell *shell_info)
{
	if (shell_info->av[1])
		exit(ft_atoi(shell_info->av[1]));
	else
		exit(shell_info->shell_exit_code);
}
