/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-18 06:54:17 by yotsurud          #+#    #+#             */
/*   Updated: 2024-09-18 06:54:17 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_env	*set_env(char **envp)
{
	t_list	*path_lst;
	t_env	*tmp;
	char	*pwd;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		print_error(strerror(errno));
	path_lst = NULL;
	path_lst = make_path_list(envp, path_lst);
	pwd = NULL;
	pwd = find_pwd(envp);
	tmp->path = path_lst;
	tmp->pwd = pwd;
	return (tmp);
}

t_list	*make_path_list(char **envp, t_list *lst)
{
	char	*str;
	char	**split;

	str = NULL;
	str = find_path(envp);
	if (str)
	{
		split = NULL;
		split = ft_split(str, ':');
		if (!split)
			print_error(strerror(errno));
		lst = make_node(split);
		if (!lst)
			print_error(strerror(errno));
	}
	return (lst);
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	*find_pwd(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

t_list	*make_node(char **split)
{
	int		i;
	t_list	*lst;
	t_list	*new;
	char	*content;

	if (!split || !(*split))
		return (NULL);
	i = 0;
	lst = NULL;
	while (split[i])
	{
		new = NULL;
		content = NULL;
		content = ft_strjoin2(split[i], "/", 1);
		if (!content)
			print_error(strerror(errno));
		new = ft_lstnew(content);
		if (!new)
			print_error(strerror(errno));
		ft_lstadd_back(&lst, new);
		i++;
	}
	free(split);
	return (lst);
}
