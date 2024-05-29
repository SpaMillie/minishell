#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_tokens
{
    char    **command;
    char    **redirect;
}   t_tokens;

typedef	struct s_alloc
{
	int	redir;
	int	other;
}	t_alloc;

// typedef struct s_list
// {
//     t_tokens token;
//     int r_num;
//     int o_num;
//     struct s_list *next;
// } t_list;

t_tokens	*createtoken(t_mini *line, int i, t_alloc *ed)
{
	t_tokens	*token;
	int			j;
	int			k;

	j = 0;
	k = 0;
	token = malloc(sizeof(t_tokens));
	if (!token)
		printf("malloc\n");
	token->command = (char **)malloc(sizeof(char *) * (ed->other + 1));
	if (!token->command)
		printf("malloc\n");
	token->redirect = (char **)malloc(sizeof(char *) * (ed->redir + 1));
	if (!token->redirect)
		printf("malloc\n");
    while (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) != 0 \
        || line->metaed[i] != NULL)
	{
		if (is_it_redirect(line->metaed[i] == 0) && ed->redir != 0)
		{
			token->redirect[j++] = ft_strdup(line->metaed[i++]);
			if (!token->redirect[j - 1] == NULL)
				printf("malloc\n");
			token->redirect[j++] = ft_strdup(line->metaed[i]);
			if (!token->redirect[j - 1] == NULL)
				printf("malloc\n");
		}
		else
		{
			token->command[k++] = ft_strdup(line->metaed[i++]);
			if (!token->redirect[k - 1] == NULL)
				printf("malloc\n");
		}
		return (token);
	}
}

int    c_count(t_mini *line, t_alloc *ed, int i)
{

    ed->redir = 0;
    ed->other = 0;
    while (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) != 0 \
        || line->metaed[i] != NULL)
    {
        if (is_it_redirect(line->metaed[i]) == 0)
        {
            ed->redir += 2;
            i++;
        }
        else
            ed->other++;
        i++;
    }
	return (i);
}

void    p_count(t_mini *line)
{
    int i;

	i = 0;
    line->pipe_num = 0;
    while (line->metaed[i] != NULL)
    {
        if (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
            line->pipe_num++;
        i++;
    }
	line->pipe_num++;
}

int	allocating_token(t_tokens *token, t_alloc *ed)
{
	token->command = malloc(sizeof(char **) * (ed->other + 1));
	if (!token->command)
		return (-1);
	token->redirect = malloc(sizeof(char **) * (ed->redir + 1));
	if (!token->redirect)
		return (-1);
	return (0);
}

void	copy_tokens(t_mini *line, t_tokens *token, int pre_i, int i)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (pre_i < i)
	{
        if (is_it_redirect(line->metaed[pre_i]) == 0)
        {
            token->redirect[k++] = ft_strdup(line->metaed[pre_i++]);
			if (!(token->redirect[k - 1]))
				printf("mallocfail\n");
            token->redirect[k++] = ft_strdup(line->metaed[pre_i++]);
			if (!(token->redirect[k - 1]))
				printf("mallocfail\n");
        }
        else
		{
            token->command[j++] = ft_strdup(line->metaed[pre_i++]);
			if (!(token->redirect[k - 1]))
				printf("mallocfail\n");
		}
	}
    token->redirect[k] = NULL;
	token->command[j] = NULL;
}

void	function(t_mini *line)
{
	t_tokens	*token;
	t_alloc		ed;
	int			prev_i;
	int			i;
	int			j;
	int			check;

	i = 0;
	j = 0;
	check = 0;
	p_count(line);
	token = malloc(sizeof(t_tokens) * (line->pipe_num));
	(!token)
		printf("malloc\n");
	while (j < line->pipe_num)
	{
		prev_i = i;
		i = c_count(line, &ed, i);
		check = allocating_token(&token[j], &ed);
		if (check == -1)
			pritnf("mallocerror\n");
		copy_tokens(&token[j], line, prev_i, i);
		j++;
	}
}



// t_list	*createnode(int redir, int other)
// {
// 	t_list	*new;

// 	new = (t_list *)malloc(sizeof(t_list));
// 	if (!new)
// 		printf("malloc fail\n");
// 	new->r_num = redir;
// 	new->o_num = other;
// 	new->token.redirect = malloc(sizeof(char *) * (redir + 1));
// 	if (!new)
// 		printf("malloc fail\n");
// }
