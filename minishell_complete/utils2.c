/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:51:42 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/17 21:23:49 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_mini *line, t_tokens **token, char *line_read, int option)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (line->metaed[i] != NULL)
	{
		if (ft_strncmp(line->metaed[i], "<<", 3) == 0)
		{
			i++;
			printf("this is where it stops\n");
			check = unlink(line->metaed[i]);
			if (check == -1)
				ft_putendl_fd("minishell: could not unlink", 2);
			i++;
		}
		else
			i++;
	}
	if (line_read)
		free(line_read);
	free_2d(line->element);
	free_2d(line->metaed);
	if (option)
		free_2d(line->envp);
	i = 0;
	while (i < line->pipe_num)
	{
		free_2d(token[i]->command);
		free_2d(token[i]->redirect);
		i++;
	}
	free(*token);
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
