/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:55:14 by yotsurud          #+#    #+#             */
/*   Updated: 2024/08/28 18:28:02 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	run_process(t_info *info, char **argv, t_env *env)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		i;

	i = -1;
	cmd = NULL;
	while (++i < info->cmd_count)
	{
		cmd = make_cmd(info, argv, env, i);
		make_fork(&pid);
		if (pid == 0)
			child_process(cmd);
		else if (pid > 0)
			parent_process(cmd);
	}
	end_process(info);
}

void	child_process(t_cmd *cmd)
{
	if (cmd->err_msg)
		exit_child_process(cmd);
	if (cmd->readfd > 0)
		dup2(cmd->readfd, 0);
	if (cmd->writefd > 0)
		dup2(cmd->writefd, 1);
	else
		dup2(cmd->pp[1], 1);
	close_fds(cmd);
	if (execve(cmd->pathname, cmd->cmd, NULL) == -1)
		exit(EXIT_FAILURE);
}

void	parent_process(t_cmd *cmd)
{
	dup2(cmd->pp[0], 0);
	close_fds(cmd);
	ft_free_cmd(cmd);
}

void	end_process(t_info *info)
{
	int	status;
	int	i;

	i = -1;
	while (++i < info->cmd_count)
	{
		if (waitpid(-1, &status, 0) == -1)
			print_error(strerror(errno));	
	}
	if (info->here_doc == YES)
	{
		unlink(FILE_NAME);
		info->here_doc = NO;
	}
}