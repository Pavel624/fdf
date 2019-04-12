/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 21:43:22 by nbethany          #+#    #+#             */
/*   Updated: 2019/01/17 01:20:52 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_next_word(char const *s, char c, size_t *start)
{
	size_t i;

	while (s[*start] == c)
		(*start)++;
	i = *start;
	while (s[*start])
	{
		if (s[*start] == c)
			break ;
		(*start)++;
	}
	return (ft_strsub(s, i, *start - i));
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s || !c)
		return (NULL);
	len = ft_count_words(s, c);
	split = (char **)ft_memalloc(sizeof(*split) * (len + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (len--)
	{
		split[i] = ft_get_next_word(s, c, &j);
		i++;
	}
	split[j] = 0;
	return (split);
}
