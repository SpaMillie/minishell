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

typedef struct s_mini
{
    char        **metaed;
    int         pipe_num;
    int         redir_num;
}   t_mini;


int is_it_redirect(char *s);

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// static size_t  ft_strlcpy(char	*dst, const char *src, size_t dstsize)
// {
// 	size_t	srcsize;
// 	size_t	i;

// 	i = 0;
// 	srcsize = ft_strlen(src);
// 	if (dstsize > 0)
// 	{
// 		while (i + 1 < dstsize && i < srcsize)
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (srcsize);
// }

// static char	*ft_strchr(const char *s, int c)
// {
// 	size_t	i;
// 	char	*ptr;

// 	i = 0;
// 	ptr = (char *)s;
// 	while (ft_strlen(ptr) >= i)
// 	{
// 		if (ptr[i] == (char)c)
// 		{
// 			ptr = (char *)&ptr[i];
// 			return (ptr);
// 		}
// 		else
// 			i++;
// 	}
// 	ptr = NULL;
// 	return (ptr);
// }

static char	*ft_strdup(const char *s1)
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

// static char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*sub_s;
// 	size_t			str_len;

// 	if (s == 0)
// 		return (0);
// 	str_len = ft_strlen(s);
// 	if (str_len < start)
// 		return (ft_strdup(""));
// 	if (len > str_len - start)
// 		len = str_len - start;
// 	sub_s = (char *)malloc(len + 1);
// 	if (sub_s == NULL)
// 		return (NULL);
// 	ft_strlcpy(sub_s, s + start, len + 1);
// 	return (sub_s);
// }

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && str1[i] != '\0')
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (str1[i] - str2[i]);
	}
	if (i < n)
		return (-str2[i]);
	return (0);
}

// int is_it_redirect(char *s)
// {
//     int len;

//     len = ft_strlen(s);
//     if (ft_strncmp(s, "<", len) == 0 || ft_strncmp(s, ">", len) == 0 || \
//         ft_strncmp(s, ">>", len) == 0 || ft_strncmp(s, "<<", len) == 0)
//         return (0);
//     return (-1);
// }

// t_tokens	*createtoken(t_mini *line, int i, t_alloc *ed)
// {
// 	t_tokens	*token;
// 	int			j;
// 	int			k;

// 	j = 0;
// 	k = 0;
// 	token = malloc(sizeof(t_tokens));
// 	if (!token)
// 		printf("malloc\n");
// 	token->command = (char **)malloc(sizeof(char *) * (ed->other + 1));
// 	if (!token->command)
// 		printf("malloc\n");
// 	token->redirect = (char **)malloc(sizeof(char *) * (ed->redir + 1));
// 	if (!token->redirect)
// 		printf("malloc\n");
//     while (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) != 0 \
//         || line->metaed[i] != NULL)
// 	{
// 		if (is_it_redirect(line->metaed[i]) == 0 && ed->redir != 0)
// 		{
// 			token->redirect[j++] = ft_strdup(line->metaed[i++]);
// 			if (!(token->redirect[j - 1]))
// 				printf("malloc\n");
// 			token->redirect[j++] = ft_strdup(line->metaed[i]);
// 			if (!(token->redirect[j - 1]))
// 				printf("malloc\n");
// 		}
// 		else
// 		{
// 			token->command[k++] = ft_strdup(line->metaed[i++]);
// 			if (!(token->redirect[k - 1]))
// 				printf("malloc\n");
// 		}
// 	}
// 	return (token);
// }

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
	token = malloc(sizeof(t_tokens *) * (line->pipe_num));
	if (!token)
		printf("malloc\n");
	while (j < line->pipe_num)
	{
		prev_i = i;
		i = c_count(line, &ed, i);
		check = allocating_token(&token[j], &ed);
		if (check == -1)
			printf("mallocerror\n");
		copy_tokens(line, &token[j], prev_i, i);
		j++;
	}
	j = 0;
	i = 0;
	while (j < line->pipe_num)
	{
		printf("j is %d", j);
		while (token[j].redirect[i] != NULL)
		{
			printf("redirect is: %s\n", token[j].redirect[i]);
			i++;
		}
		i = 0;
		while (token[j].command[i] != NULL)
		{
			printf("command is: %s\n", token[j].command[i]);
			i++;
		}
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
