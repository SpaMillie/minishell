/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 22:13:03 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, char *str)
{
	char	*env;
	char	*env_value;
	int		i;

	env = ft_getenv(envp, str);
	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	env_value = ft_substr(env, i, ft_strlen(env));
	return (env_value);
}

char	*ft_getenv(char **envp, char *str)
{
	int		i;
	char	*path_pointer;
	int		len;

	i = 0;
	path_pointer = NULL;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, len) && envp[i][len] == '=')
		{
			path_pointer = ft_strdup(envp[i]);
			if (!path_pointer)
				malloc_failure(line); //another malloc_failure
			break ;
		}
		i++;
	}
	if (!path_pointer)
		return (NULL);
	return (path_pointer);
}

static char	**create_paths(char **tokens, char **envp)
{
	char	*path_pointer;
	char	**paths;
	int		i;

	path_pointer = ft_getenv(envp, "PATH");
	if (!path_pointer)
		return (NULL);
	paths = ft_split(path_pointer, ':');
	if (!paths)
		return (NULL);
	free(path_pointer);
	i = 0;
	while (paths[i])
	{
		paths[i] = join_and_free(paths[i], "/");
		paths[i] = join_and_free(paths[i], tokens[0]);
		i++;
	}
	return (paths);
}

char	*get_path(char **tokens, char **envp)
{
	int		i;
	char	*res;
	char	**paths;

	if (!ft_strncmp(tokens[0], "./", 2))
	{
		res = ft_strdup(tokens[0]);
		if (!res)
			malloc_failure(line);//another malloc_failure1 
		return (res);
	}
	paths = create_paths(tokens, envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			res = ft_strdup(paths[i]);
			if (!res)
				exit(1);
			free_2d(paths);
			return (res);
		}
		i++;
	}
	free_2d(paths);
	print_error("command not found", tokens);
	return (NULL);
}