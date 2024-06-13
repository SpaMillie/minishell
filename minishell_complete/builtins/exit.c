/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:43:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/13 19:49:43 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	non_numeric_arg(char **args)
{
	int	i;
	int	num;

	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			print_error("numeric argument required", args);
			exit(255);
		}
		i++;
	}
	num = ft_atoi(args[1]);
	exit(num);
}

void	exit_cmd(char **args, t_mini *line)
{
	int	i;

	ft_printf("exit\n");
	i = 0;
	while (args[i])
		i++;
	printf("i is %d\n", i);
	if (i > 2)
	{
		line->err_num = 1;
		print_error("too many arguments", args);
		return ;
	}
	else if (i > 1)
		non_numeric_arg(args);
	else if (i == 1)
		exit(0);
}
