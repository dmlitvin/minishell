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

static char	**compress_env(t_minishell *shell_info)
{
	t_variable		*variable;
	size_t			i;
	t_list			*list;
	char			**env;
	const size_t	env_count = ft_list_size(shell_info->env_list);

	env = malloc(sizeof(char*) * (env_count + 1));
	i = 0;
	list = shell_info->env_list;
	while (list)
	{
		variable = list->content;
		env[i++] = ft_strcat(ft_strcat(ft_strcat(ft_memalloc(
				ft_strlen(variable->key) + ft_strlen(variable->value) + 2),
						variable->key), "="), variable->value);
		list = list->next;
	}
	env[i] = 0;
	return (env);
}

static char	*get_path(t_minishell *shell_info)
{
	void	*memory_ptr;
	char	*path;
	char	**paths;

	if (ft_strchr(shell_info->av[0], '/'))
		return (ft_strdup(shell_info->av[0]));
	paths = ft_strsplit(get_env("PATH", shell_info), ':');
	path = find_executable(paths, shell_info);
	memory_ptr = paths;
	if (paths)
		while (*paths)
			free(*paths++);
	free(memory_ptr);
	return (path);
}

static void	find_run_executable(t_minishell *shell_info)
{
	char	**env;
	void	*tmp;
	char	*path;
	pid_t	pid;

	if (!(path = get_path(shell_info)))
	{
		ft_putendl_fd(RED"No such command"EOM, 2);
		return ;
	}
	env = compress_env(shell_info);
	if ((pid = fork()))
		waitpid(pid, &shell_info->last_exit_code, 0);
	else if (execve(path, shell_info->av, env) == -1)
	{
		ft_putstr_fd(RED, 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_putstr_fd(EOM, 2);
		exit(1);
	}
	free(path);
	tmp = env;
	while (*env)
		free(*env++);
	free(tmp);
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
