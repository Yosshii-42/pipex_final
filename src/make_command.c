/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-25 06:25:21 by yotsurud          #+#    #+#             */
/*   Updated: 2024-08-25 06:25:21 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_cmd	*make_cmd(t_info *info, char **argv, t_env *env, int index)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	if (pipe(cmd->pp) == -1)
		print_error(strerror(errno));
	if (index == 0)
		open_read_file(cmd, info, argv[info->infile_index]);
	if (index == info->cmd_count - 1)
		open_write_file(cmd, info, argv[info->outfile_index]);
	cmd->pathname = make_path_and_cmd(argv[info->cmd_start + index], cmd, env);
	if (!cmd->pathname)
		print_error(strerror(errno));
	if (access(cmd->pathname, F_OK & X_OK) != 0 && !cmd->cmd)
		set_err_message(cmd, cmd->pathname);
	else if (access(cmd->pathname, F_OK & X_OK) != 0)
		set_err_message(cmd, cmd->cmd[0]);
	return (cmd);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->readfd = -1;
	cmd->writefd = -1;
	cmd->pp[0] = -1;
	cmd->pp[1] = -1;
	cmd->pathname = NULL;
	cmd->cmd = NULL;
	cmd->err_msg = NULL;
}

char	*make_path_and_cmd(char *str, t_cmd *cmd, t_env *env)
{
	if (!str)
		return (NULL);
	else if (*str && !ft_strlen(str))
		return (return_str(""));
	else if (str[0] == ' ' || str[ft_strlen(str) - 1] == ' ')
		return (return_str(str));
	else
	{
		cmd->cmd = ft_split(str, ' ');
		if ((cmd->cmd[0]))
		{
			if (cmd->cmd[0][0] == '/')
				return (return_str(cmd->cmd[0]));
			else if (cmd->cmd[0][0] == '.')
				return (make_pwd_path(cmd->cmd[0], env));
			else
				return (check_access(cmd->cmd[0], env));
		}
	}
	return (str);
}

char	*make_pwd_path(char *command, t_env *env)
{
	char	*str;

	if (!env->pwd)
		return (NULL);
	str = NULL;
	str = ft_strjoin(env->pwd, "/");
	if (!str)
		return (NULL);
	str = ft_strjoin2(str, command, 1);
	if (!str)
		return (NULL);
	return (str);
}

char	*check_access(char *command, t_env *env)
{
	char	*str;
	t_list	*start;

	start = env->path;
	str = NULL;
	if (!env->path)
	{
		str = make_pwd_path(command, env);
		if (!access(str, F_OK & X_OK))
			return (str);
	}
	while (env->path)
	{
		str = make_string(command, env->path->content);
		if (!str)
			print_error(strerror(errno));
		if (!access(str, F_OK & X_OK))
			return (env->path = start, str);
		else
			env->path = env->path->next;
		free(str);
		str = NULL;
	}
	return (env->path = start, return_str(command));
}
