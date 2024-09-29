/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:51:33 by yotsurud          #+#    #+#             */
/*   Updated: 2024/08/11 15:06:15 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free(char **str, int i)
{
	char	**tmp;

	tmp = str;
	if (!str)
		return ;
	while (tmp[i])
		free(tmp[i++]);
	if (str)
		free(str);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split[0] || !split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_free_cmd(t_cmd *cmd)
{
	int	i;

	if (*(cmd->pathname))
		free(cmd->pathname);
	i = 0;
	if (cmd->cmd)
	{
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}
	if (cmd->err_msg)
		free(cmd->err_msg);
	free(cmd);
}

void	ft_env_clear(t_env *env)
{
	ft_lstclear(&(env->path));
	free(env);
}
