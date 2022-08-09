/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:20:49 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/19 19:10:15 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int	i;	
	int	res;

	i = 0;
	res = 1;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			while (s[i] == c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				break ;
			res++;
		}
		i++;
	}	
	return (res);
}

static int	len_n_word(char const *s, char c, int n)
{
	int	i;
	int	word;
	int	len;

	i = 0;
	len = 0;
	word = 0;
	while (s[i] == c)
		i++;
	while (word < n)
	{
		while (s[i] != c)
			i++;
		while (s[i] == c)
			i++;
		word++;
	}
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void	copy_n_word(char *dst, char const *s, char c, int pos)
{
	int	j;
	int	i;
	int	word;

	word = 0;
	i = 0;
	j = 0;
	while (s[i] == c)
		i++;
	while (word < pos)
	{
		while (s[i] != c)
			i++;
		while (s[i] == c)
			i++;
		word++;
	}
	while (s[i] != c && s[i] != '\0')
		dst[j++] = s[i++];
	dst[j++] = '\0';
}

char	**ft_strsplit(char const *s, char c)
{
	int		words;
	char	**array;
	int		i;

	if (s == NULL)
		return (NULL);
	words = ft_words(s, c);
	array = (char **) malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < words)
	{
		array[i] = (char *) malloc(sizeof(char) * len_n_word(s, c, i) + 1);
		if (!array[i])
			return (NULL);
		copy_n_word(array[i], s, c, i);
		i++;
	}
	array[i] = NULL;
	return (array);
}
