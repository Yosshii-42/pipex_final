/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:21:08 by yotsurud          #+#    #+#             */
/*   Updated: 2024/08/13 17:20:28 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "./libft/includes/libft.h"
# include "./libft/includes/ft_printf.h"
# include "./libft/includes/get_next_line.h"

# define FILE_NAME "2qryY0jwPY2AXF0VxD2CTIX3uv03Bi"
# define YES (0)
# define NO (1)

typedef struct s_info
{
	int		cmd_start;
	int		cmd_count;
	int		infile_index;
	int		outfile_index;
	int		here_doc;
	char	*eof;
}		t_info;

typedef struct s_env
{
	t_list	*path;
	char	*pwd;
}		t_env;

typedef struct s_cmd
{
	int		readfd;
	int		writefd;
	int		pp[2];
	char	*pathname;
	char	**cmd;
	char	*err_msg;
}		t_cmd;

//init
void	init(int argc, char **argv, t_info *cmd_info);
void	here_doc_process(t_info *info);

//find string from envp
char	*find_path(char **envp);
char	*find_pwd(char **envp);

//path list
t_env	*set_env(char **envp);
t_list	*make_path_list(char **envp, t_list *lst);
t_list	*make_node(char **split);

//command
t_cmd	*make_cmd(t_info *info, char **argv, t_env *env, int index);
void	init_cmd(t_cmd *cmd);
void	open_read_file(t_cmd *cmd, t_info *info, char *str);
void	open_write_file(t_cmd *cmd, t_info *info, char *str);
char	*make_path_and_cmd(char *str, t_cmd *array, t_env *env);
char	**cpy_path_to_cmd(char *str);
char	*check_access(char *command, t_env *env);
char	*make_pwd_path(char *command, t_env *env);
char	*return_str(char *str);

//process
void	run_process(t_info *cmd_info, char **argv, t_env *env);
void	child_process(t_cmd *cmd);
void	parent_process(t_cmd *cmd);
void	end_process(t_info *info);

//process_utils
void	make_fork(pid_t *pid);
void	close_fds(t_cmd *cmd);
void	exit_child_process(t_cmd *cmd);

//dup_and_join
char	*ft_strjoin2(char *s1, char *s2, int select);
char	*make_string(char *command, char *path);

//free_and_exit
void	ft_free(char **str, int i);
void	ft_free_split(char **split);
void	ft_free_cmd(t_cmd *cmd);
void	ft_env_clear(t_env *env);

//error_message
void	print_error(char *err_message);
void	set_err_message(t_cmd *array, char *str);
void	set_file_err(t_cmd *cmd, char *filename, char *err_msg);//, int *fd_status);

#endif
