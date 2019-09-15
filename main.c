/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:29:01 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/12 15:29:01 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	print_promt(t_minishell *shell_info)
{
	ft_putstr(shell_info->last_exit_code ? RED : GREEN);
	ft_putstr("lol -> "EOM);
}

static inline void	clear_cycle(t_minishell *shell_info)
{
	char	**av;

	av = shell_info->av;
	while (*av)
		free(*av++);
	free(shell_info->av);
	free(shell_info->line);
}

int					main(int ac, char **av, char **env)
{
	t_minishell	*shell_info;

	(void)ac;
	(void)av;
	shell_info = malloc(sizeof(t_minishell));
	shell_info->env_list = init_variables(env);
	shell_info->last_exit_code = 0;
	shell_info->shell_exit_code = 0;
	print_promt(shell_info);
	while (get_next_line(0, &shell_info->line))
	{
		shell_info->av = split_arguments(shell_info->line);
		execute_command(shell_info);
		clear_cycle(shell_info);
		print_promt(shell_info);
		if (shell_info->last_exit_code)
			shell_info->shell_exit_code = 1;
	}
	ft_putchar('\n');
	return (shell_info->shell_exit_code);
}
