/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-26 07:04:43 by yotsurud          #+#    #+#             */
/*   Updated: 2024-08-26 07:04:43 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin2(char *s1, char *s2, int select)
{
	int		i;
	int		j;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	if (!(*s1))
		result = (char *)ft_calloc(ft_strlen(s2) + 1, sizeof(char));
	else
		result = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1,
				sizeof(char));
	if (!result)
		return (NULL);
	while (s1[++i])
		result[i] = s1[i];
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	if (select == 1 && *s1)
		free(s1);
	else if (select == 2 && *s2)
		free(s2);
	return (result);
}

char	*make_string(char *command, char *path)
{
	char	*str;

	if (!command)
		return (NULL);
	str = NULL;
	str = ft_strdup(command);
	if (!str)
		return (NULL);
	str = ft_strjoin2(path, str, 2);
	if (!str)
		return (NULL);
	return (str);
}

void	print_error(char *err_message)
{
	ft_printf(2, "%s\n", err_message);
	exit(1);
}

void	set_err_message(t_cmd *array, char *str)
{
	if (array->err_msg)
		return ;
	array->err_msg = NULL;
	if (!str || !*str)
		array->err_msg = ft_strdup("Command ' ' not found\n");
	else
		array->err_msg = ft_strjoin2(str, ": command not found\n", 0);
	if (!array->err_msg)
		print_error(strerror(errno));
}
