/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milica <milica@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/24 11:24:28 by milica           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_strings(char *str1, char *str2, char *str3, char *str4)
{
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

static int	check_args(char **args, t_mini *line)
{
	char	*home;

	if (!args[1])
	{
		home = get_env_value(line->envp, "HOME", line);
		if (chdir(home) == -1)
		{
			line->err_num = 1;
			print_error("No such file or directory", args);
			return (1);
		}
		free(home);
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			line->err_num = 1;
			print_error("No such file or directory", args);
			return (1);
		}
	}
	return (0);
}

static char	*cd_error_check(char **args, t_mini *line)
{
	char	*old_pwd_path;

	if (args[1] && args[2])
		print_error("Too many arguments", args);
	old_pwd_path = getcwd(NULL, 0);
	if (!old_pwd_path)
	{
		ft_putendl_fd("getcwd error", 2);
		exit(1);
	}
	if (check_args(args, line) == 1)
	{
		free(old_pwd_path);
		return (NULL);
	}
	else
		return (old_pwd_path);
}

void	cd(char **args, t_mini *line)
{
	char	*old_pwd_path;
	char	*new_pwd;
	char	*old_pwd;
	char	*new_pwd_path;

	old_pwd_path = cd_error_check(args, line);
	if (!old_pwd_path)
		return ;
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_path);
	if (!old_pwd)
		malloc_failure(line);
	new_pwd_path = getcwd(NULL, 0);
	if (!new_pwd_path)
		exit(1);
	new_pwd = ft_strjoin("PWD=", new_pwd_path);
	if (!new_pwd)
		malloc_failure(line);
	export(old_pwd, line);
	export(new_pwd, line);
	free_strings(old_pwd, new_pwd, old_pwd_path, new_pwd_path);
}
