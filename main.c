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
	ft_putstr(" -> "EOM);
}

static inline void	clear_cycle(t_minishell *shell_info)
{
	char	*last_code;
	char	**av;

	av = shell_info->av;
	while (*av)
		free(*av++);
	free(shell_info->av);
	free(shell_info->line);
	ft_lstadd(&shell_info->env_list, make_variable("0",
		(last_code = ft_itoa(shell_info->last_exit_code))));
	free(last_code);
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
		check_expansion(shell_info);
		execute_command(shell_info);
		clear_cycle(shell_info);
		print_promt(shell_info);
		if (shell_info->last_exit_code)
			shell_info->shell_exit_code = 1;
	}
	ft_putchar('\n');
	return (shell_info->shell_exit_code);
}
