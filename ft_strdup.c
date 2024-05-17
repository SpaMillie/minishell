/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:39:35 by mspasic           #+#    #+#             */
/*   Updated: 2024/05/17 17:35:49 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "./include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_cpy;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s1_cpy = (char *)malloc(i + 1);
	if (s1_cpy == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s1_cpy[i] = (char)s1[i];
		i++;
	}
	s1_cpy[i] = '\0';
	return (s1_cpy);
}
/*
int	main(void)
{
	char *str = "The final frontier";
	char *str1;

	str1 = ft_strdup(str);
	printf("The string is: %s", str1);
	free(str1);
	return (0);
}*/
