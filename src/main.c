/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:57:19 by yotsurud          #+#    #+#             */
/*   Updated: 2024/08/11 15:05:16 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_info	cmd_info;

	if (argc < 5)
	{
		ft_printf(2, "Error\n");
		exit(1);
	}
	init(argc, argv, &cmd_info);
	env = NULL;
	env = set_env(envp);
	run_process(&cmd_info, argv, env);
	ft_env_clear(env);
	exit(EXIT_SUCCESS);
}

void	init(int argc, char **argv, t_info *cmd_info)
{
	if (!ft_memcmp(argv[1], "here_doc", 9))
	{
		cmd_info->cmd_start = 3;
		cmd_info->cmd_count = argc - 4;
		cmd_info->infile_index = -1;
		cmd_info->here_doc = YES;
		if (ft_strlen(argv[2]) == 0)
			exit(EXIT_FAILURE);
		else
			cmd_info->eof = argv[2];
		here_doc_process(cmd_info);
	}
	else
	{
		cmd_info->cmd_start = 2;
		cmd_info->cmd_count = argc - 3;
		cmd_info->infile_index = 1;
		cmd_info->here_doc = NO;
		cmd_info->eof = NULL;
	}
	cmd_info->outfile_index = argc - 1;
}

void	here_doc_process(t_info *info)
{
	char	*str;
	int		fd;

	fd = open(FILE_NAME, O_CREAT | O_RDWR, 0600);
	if (fd < 0)
		exit(EXIT_FAILURE);
	str = NULL;
	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
			break ;
		if (ft_memcmp(str, info->eof, ft_strlen(info->eof) + 1) == 10 || !str)
		{
			if (*str)
				free(str);
			break ;
		}
		ft_printf(fd, "%s", str);
		free(str);
		str = NULL;
	}
	close(fd);
}
