/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:17:42 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/15 17:17:50 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_variable(char **line_ptr, t_minishell *shell_info)
{
	const char	*var_value = get_env(*line_ptr + 1, shell_info);
	char		*new_line;

	if (var_value)
		new_line = ft_strdup(var_value);
	else
		new_line = ft_stralloc(0);
	free(*line_ptr);
	*line_ptr = new_line;
}

static void	replace_tilde(char **line_ptr, t_minishell *shell_info)
{
	char		*new_value;

	if (line_ptr[0][1] == '+')
		new_value = ft_strdup(get_env("PWD", shell_info));
	else if (line_ptr[0][1] == '-')
		new_value = ft_strdup(get_env("OLDPWD", shell_info));
	else if (!line_ptr[0][1])
		new_value = ft_strdup(get_env("HOME", shell_info));
	else if (line_ptr[0][1] == '/')
		new_value = ft_strcat(ft_strcat(ft_memalloc(ft_strlen(get_env("HOME",
				shell_info) + 2)), get_env("HOME", shell_info)), "/");
	else
		new_value = ft_stralloc(0);
	free(*line_ptr);
	*line_ptr = new_value;
}

void	check_expansion(t_minishell *shell_info)
{
	char	**line_ptr;

	line_ptr = shell_info->av;
	while (*line_ptr)
	{
		if (**line_ptr == '$')
			replace_variable(line_ptr, shell_info);
		else if (**line_ptr == '~' && ft_strlen(*line_ptr) < 3)
			replace_tilde(line_ptr, shell_info);
		line_ptr++;
	}
}
