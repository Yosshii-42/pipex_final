/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:54:06 by yotsurud          #+#    #+#             */
/*   Updated: 2024/05/15 15:19:58 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_i(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*ft_make_string_i(char const *s, char c)
{
	size_t	j;
	size_t	len;
	char	*str;

	len = 0;
	while (s[len] && (s[len] != c))
		len++;
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (j < len)
	{
		str[j] = s[j];
		j++;
	}
	return (str);
}

static void	*ft_free(char **result, int i)
{
	while (result[i])
		free(result[i--]);
	if (result)
		free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)ft_calloc(ft_count_i(s, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			result[i] = ft_make_string_i(s, c);
			if (!result[i])
				return (ft_free(result, i));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (result);
}
