/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 22:09:36 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_prompt(void)
{
	char	*cwd;
	char	*username;
	char	*hostname;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(1);
	username = getenv("USER");
	if (!username)
		username = "unknown";
	hostname = getenv("HOSTNAME");
	if (!hostname)
		hostname = "unknown";
	prompt = ft_strdup(username);
	prompt = join_and_free(prompt, "@");
	prompt = join_and_free(prompt, hostname);
	prompt = join_and_free(prompt, ":");
	prompt = join_and_free(prompt, cwd);
	free(cwd);
	prompt = join_and_free(prompt, "$ ");
	return (prompt);
}

// static void	free_all(char *line_read, t_tokens *token, t_mini *line)
// {
// 	int	i;

// 	free(line_read);
// 	free_2d(line->metaed);
// 	i = 0;
// 	while (token[i].command && token[i].command[0])
// 	{
// 		free_2d(token[i].command);
// 		i++;
// 	}
// 	i = 0;
// 	while (token[i].redirect && token[i].redirect[0])
// 	{
// 		free_2d(token[i].redirect);
// 		i++;
// 	}
// }
static void	to_token(t_mini *line, t_tokens *token)
{			
		p_count(line);
		token = malloc(sizeof(t_tokens) * (line->pipe_num));
		if (!token)
			malloc_failure(line);
		tokenising(line, token);
}

static int	prompting(char *line_read)
{			
		char *prompt;

		prompt = create_prompt();
		line_read = readline(prompt);
		if (!line_read)
			return (1); // NULL if failed to allocate?
		free(prompt);
		return (1);
}

static int	minishell_loop(t_mini *line)
{
	t_tokens	*token;
	char		*line_read;
	
	token = (t_tokens *){0};
	line_read = NULL;
	printf("entered minishell_loop\n");
	while (1)
	{			
		if (prompting(line_read) == 1)
			return (1);
		if (ft_strlen(line_read) == 0)
			continue ;
		add_history(line_read);
		to_token(line, token);
		validating(line_read, line);
		expansion(line);
		to_token(line, token);
		execute(token, line);
		cleanup(line, token, line_read);
	}
	printf("exited minishell_loop\n");
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini				line;
	struct sigaction	sa;

	(void)argv;
	line = (t_mini){0};
	line.envp = envp_dup(envp);
	if (!line.envp)
		malloc_failure(&line); //figure out what to free
	export("OLDPWD", &line);
	set_term_attr();
	if (argc == 1)
	{
		printf("entered the condition\n");
		sa.sa_handler = handle_signal;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
		if (minishell_loop(&line) == 1)
			return (1);
		printf("exited the condition\n");
	}
	return (0);
}