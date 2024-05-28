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

typedef struct s_list
{
    t_tokens token;
    int r_num;
    int o_num;
    struct s_list *next;
} t_list;

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

void    c_count(t_mini *line, t_alloc *ed, int i, int end)
{

    ed->redir = 0;
    ed->other = 0;
    // while (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) != 0 \
    //     || line->metaed[i] != NULL)
	while (i < end)
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

void	function(t_mini *line)
{
	t_tokens	*token;
	int			i;

	i = 0;
	p_count(line);
	token = malloc(sizeof(t_tokens) * (line->pipe_num));
	(!token)
		printf("malloc\n");
	while (i < line->pipe_num)
	{
		c_count(line, &token[i])
		token[i] = 
		i++;
	}
}


t_list	*createnode(int redir, int other)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		printf("malloc fail\n");
	new->r_num = redir;
	new->o_num = other;
	new->token.redirect = malloc(sizeof(char *) * (redir + 1));
	if (!new)
		printf("malloc fail\n");
}
