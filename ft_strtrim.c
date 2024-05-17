/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:48:25 by mspasic           #+#    #+#             */
/*   Updated: 2024/05/17 17:36:16 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./include/libft.h"
#include <stdio.h>
#include <stdlib.h>

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

static int	ft_check(char c, const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_s1;
	size_t	j;
	size_t	i;
	size_t	k;

	if (!s1)
		return (NULL);
	i = 0;
	k = 0;
	j = ft_strlen(s1) - 1;
	while (ft_check (s1[i], set) == 1)
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_check(s1[j], set) == 1)
		j--;
	new_s1 = (char *)malloc(j - i + 2);
	if (new_s1 == NULL)
		return (NULL);
	while (i <= j)
		new_s1[k++] = s1[i++];
	new_s1[k] = '\0';
	return (new_s1);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim("  \t  \t \n   \n\n\n\t", " \n\t"));
	return (0);
}*/
