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

void		echo(t_minishell *shell_info)
{
	char	**av;

	if (shell_info->av[1])
		ft_putstr(shell_info->av[1]);
	av = shell_info->av[1] ? shell_info->av + 2 : shell_info->av + 1;
	while (*av)
	{
		if (**av)
			ft_printf(" %s", *av++);
		av++;
	}
	ft_putchar('\n');
	shell_info->last_exit_code = 0;
}

static char	*get_path(t_minishell *shell_info)
{
	if (ft_strequ(shell_info->av[1], "-"))
		return (get_env("OLDPWD", shell_info));
	else if (ft_strequ(shell_info->av[1], "--") && !shell_info->av[2])
		return (get_env("HOME", shell_info));
	else if (ft_strequ(shell_info->av[1], "--") && shell_info->av[2])
		return (shell_info->av[2]);
	else if (shell_info->av[1])
		return (shell_info->av[1]);
	return (get_env("HOME", shell_info));
}

static void	change_variables(char *oldpwd, char *pwd, t_minishell *shell_info)
{
	if (ft_lstfind(shell_info->env_list, "OLDPWD", key_cmp))
		delete_env("OLDPWD", shell_info);
	if (ft_lstfind(shell_info->env_list, "PWD", key_cmp))
		delete_env("PWD", shell_info);
	ft_lstadd(&shell_info->env_list, make_variable("OLDPWD", oldpwd));
	ft_lstadd(&shell_info->env_list, make_variable("PWD", pwd));
}

void		cd(t_minishell *shell_info)
{
	char	oldpwd[1024];
	char	newpwd[1024];
	char	*path;

	ft_bzero(oldpwd, sizeof(oldpwd));
	ft_bzero(newpwd, sizeof(newpwd));
	path = get_path(shell_info);
	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(path) == -1)
	{
		if (access(path, 0))
			ft_putstr_fd("cd : file not found: ", 2);
		else if (access(path, 3))
			ft_putstr_fd("cd : permission denied: ", 2);
		else
			ft_putstr_fd("cd : string not in pwd: ", 2);
		ft_putendl_fd(path, 2);
	}
	getcwd(newpwd, sizeof(newpwd));
	change_variables(oldpwd, newpwd, shell_info);
}

void		exit_shell(t_minishell *shell_info)
{
	if (shell_info->av[1])
		exit(ft_atoi(shell_info->av[1]));
	else
		exit(shell_info->shell_exit_code);
}
