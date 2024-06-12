/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:51:42 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 20:12:09 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_mini *line, t_tokens *token, char *line_read)
{
	free(line_read);
	free_2d(line->element);
	free_2d(line->metaed);
	free_2d(token->command);
	free_2d(token->redirect);
	free(token);
	free(line);
}

void	free_2d(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

char	*join_and_free(char *prompt, char *str)
{
	char	*temp;

	temp = ft_strjoin(prompt, str);
	if (!temp)
	{
		free(prompt);
		malloc_failure();
	}
	free(prompt);
	prompt = temp;
	return (prompt);
}
