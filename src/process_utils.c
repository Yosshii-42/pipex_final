/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-28 08:42:02 by yotsurud          #+#    #+#             */
/*   Updated: 2024/08/28 18:36:10 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	make_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		print_error(strerror(errno));
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->readfd > 0)
		close(cmd->readfd);
	if (cmd->writefd > 0)
		close(cmd->writefd);
	close(cmd->pp[0]);
	close(cmd->pp[1]);
}

char	*return_str(char *str)
{
	char	*copy;
	int		len;
	int		i;

	len = ft_strlen(str);
	copy = NULL;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < len)
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

void	exit_child_process(t_cmd *cmd)
{
	if (cmd->err_msg)
		ft_printf(2, "%s", cmd->err_msg);
	close_fds(cmd);
		exit(EXIT_FAILURE);
}
