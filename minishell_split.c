/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:05:36 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/15 12:05:37 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_size(char *line)
{
	int	size;

	size = 0;
	while (ft_is_whitespace(line))
		++line;
	while (*line)
	{
		++size;
		if (*line == '\'' || *line == '\"' || *line == '`')
		{
			if (!(line = ft_strchr(line + 1, *line)))
				return (-1);
			else
				continue ;
		}
		while (*line && !ft_is_whitespace(line))
			++line;
		while (ft_is_whitespace(line))
			++line;
	}
	return (size);
}

static void	split_into(char **argv, char *line)
{
	char	*tmp;

	while (ft_is_whitespace(line))
		++line;
	while (*line)
	{
		tmp = line;
		if (*tmp == '\'' || *tmp == '\"' || *tmp == '`')
		{
			line = ft_strchr(line + 1, *line) + 1;
			*argv++ = ft_strsub(tmp + 1, 0, line - tmp - 2);
			while (ft_is_whitespace(line))
				++line;
			continue ;
		}
		while (*line && !ft_is_whitespace(line))
			++line;
		*argv++ = ft_strsub(tmp, 0, line - tmp);
		while (ft_is_whitespace(line))
			++line;
	}
	*argv = NULL;
}

char		**split_arguments(char *line)
{
	char	**argv;
	int		argv_size;

	argv_size = count_size(line);
	if (argv_size == -1)
	{
		argv = malloc(sizeof(char*));
		*argv = 0;
		ft_printf("bad quote\n");
	}
	else if (argv_size == 0)
	{
		argv = malloc(sizeof(char*));
		*argv = 0;
	}
	else
	{
		argv = malloc(sizeof(char*) * (argv_size + 1));
		split_into(argv, line);
	}
	return (argv);
}
