/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:11:22 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/16 18:11:29 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_file(const char *path, const char *filename)
{
	struct dirent	*file_ptr;
	DIR				*dir_ptr;

	if ((dir_ptr = opendir(path)))
	{
		while ((file_ptr = readdir(dir_ptr)))
			if (ft_strequ(file_ptr->d_name, filename))
			{
				closedir(dir_ptr);
				return (1);
			}
		closedir(dir_ptr);
	}
	else
		return (-1);
	return (0);
}

char		*find_executable(char **paths, t_minishell *shell_info)
{
	int		file_find_result;

	while (*paths)
	{
		file_find_result = find_file(*paths, shell_info->av[0]);
		if (file_find_result == 1)
			return (ft_strcat(ft_strcat(ft_strcat(ft_memalloc(ft_strlen(
					*paths) + ft_strlen(shell_info->av[0]) + 2),
							*paths), "/"), shell_info->av[0]));
		else if (file_find_result == -1)
		{
			shell_info->last_exit_code = 1;
			return (0);
		}
		paths++;
	}
	shell_info->last_exit_code = 1;
	return (0);
}
