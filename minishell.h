/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:28:57 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/12 15:28:58 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef	struct	s_variable
{
	char		*key;
	char		*value;
}				t_variable;

typedef struct	s_minishell
{
	char		*line;
	char		**av;
	t_list		*env_list;
	int			last_exit_code;
	int			shell_exit_code;
}				t_minishell;

extern const char	*g_built_in_list[];
extern void			(*g_built_in_func_list[])(t_minishell*);

t_list			*init_variables(char **env);
t_list			*make_variable(char *key, char *value);
void			delete_env(char *key, t_minishell *shell_info);
char			**split_arguments(char *line);

void			execute_command(t_minishell *shell_info);

void			echo(t_minishell *shell_info);
void			cd(t_minishell *shell_info);
void			env(t_minishell *shell_info);
void			set_env(t_minishell *shell_info);
void			unset_env(t_minishell *shell_info);
void			exit_shell(t_minishell *shell_info);

#endif
