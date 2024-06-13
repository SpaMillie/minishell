/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:51:42 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/13 13:50:29 by mspasic          ###   ########.fr       */
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

	if (!prompt)
		return (NULL); //if the previous join_and_free fails so we don't add checks after everything
	temp = ft_strjoin(prompt, str);
	free(prompt);
	if (!temp)
	{
		//malloc_failure
		return (NULL);
	}
	prompt = temp;
	return (prompt);
}
