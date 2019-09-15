/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:50:31 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/12 15:50:32 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_variable(void *content, size_t content_size)
{
	const t_variable	*variable = content;

	(void)content_size;
	free(variable->key);
	free(variable->value);
	free(content);
}

static t_list	*del_get_next(t_list *lst)
{
	t_list	*next;

	next = lst->next;
	ft_lstdelone(&lst, del_variable);
	return (next);
}

void		delete_env(char *key, t_minishell *shell_info)
{
	t_list		*list;

	shell_info->last_exit_code = 0;
	list = shell_info->env_list;
	if (ft_strequ(((t_variable*)list->content)->key, key))
	{
		shell_info->env_list = del_get_next(list);
		return ;
	}
	while (list->next)
	{
		if (ft_strequ(((t_variable*)list->next->content)->key, key))
		{
			list->next = del_get_next(list->next);
			return ;
		}
		list = list->next;
	}
	shell_info->last_exit_code = 1;
}

t_list		*make_variable(char *key, char *value)
{
	size_t		str_size;
	t_variable	variable;

	str_size = ft_strlen(key);
	variable.key = ft_memcpy(malloc(str_size + 1), key, str_size + 1);
	str_size = ft_strlen(value);
	variable.value = ft_memcpy(malloc(str_size + 1), value, str_size + 1);
	return (ft_lstnew(&variable, sizeof(t_variable)));
}

t_list		*init_variables(char **env)
{
	char	*key;
	char	*value;
	t_list	*list;

	list = NULL;
	while (*env)
	{
		value = ft_strchr(*env, '=');
		key = *env++;
		*value = 0;
		ft_lstadd_end(&list, make_variable(key, value + 1));
	}
	return (list);
}
