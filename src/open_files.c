/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-18 06:52:10 by yotsurud          #+#    #+#             */
/*   Updated: 2024-09-18 06:52:10 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_read_file(t_cmd *cmd, t_info *info, char *str)
{
	if (info->here_doc == YES)
	{
		cmd->readfd = open(FILE_NAME, O_RDONLY);
		if (cmd->readfd < 0)
			set_file_err(cmd, FILE_NAME, strerror(errno));
	}
	else
	{
		cmd->readfd = open(str, O_RDONLY);
		if (cmd->readfd < 0)
			set_file_err(cmd, str, strerror(errno));
	}
}

void	open_write_file(t_cmd *cmd, t_info *info, char *str)
{
	if (info->here_doc == YES)
	{
		cmd->writefd = open(str, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (cmd->writefd < 0 && cmd->readfd < 0)
			set_file_err(cmd, str, strerror(errno));
	}
	else
	{
		cmd->writefd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (cmd->writefd < 0 && cmd->readfd < 0)
			set_file_err(cmd, str, strerror(errno));
	}
}

void	set_file_err(t_cmd *cmd, char *filename, char *err_msg)
{
	char	*message;

	message = NULL;
	message = ft_strjoin("bash: ", filename);
	if (!message)
		print_error(strerror(errno));
	message = ft_strjoin2(message, ": ", 1);
	if (!message)
		print_error(strerror(errno));
	message = ft_strjoin2(message, err_msg, 1);
	if (!message)
		print_error(strerror(errno));
	message = ft_strjoin2(message, "\n", 1);
	if (!message)
		print_error(strerror(errno));
	cmd->err_msg = message;
}
