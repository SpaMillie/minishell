
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// #define TRUE 1
// #define FALSE 0

//most printf's should be exits

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

void	function(t_mini *line);

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static size_t  ft_strlcpy(char	*dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	i = 0;
	srcsize = ft_strlen(src);
	if (dstsize > 0)
	{
		while (i + 1 < dstsize && i < srcsize)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

static char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (ft_strlen(ptr) >= i)
	{
		if (ptr[i] == (char)c)
		{
			ptr = (char *)&ptr[i];
			return (ptr);
		}
		else
			i++;
	}
	ptr = NULL;
	return (ptr);
}

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

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_s;
	size_t			str_len;

	if (s == 0)
		return (0);
	str_len = ft_strlen(s);
	if (str_len < start)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	sub_s = (char *)malloc(len + 1);
	if (sub_s == NULL)
		return (NULL);
	ft_strlcpy(sub_s, s + start, len + 1);
	return (sub_s);
}

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

// char	*minishell_substr(char *s, int strt, size_t len)
// {
// 	char	*sub_s;
// 	char	c;

// 	if (s[strt] == '\'' || s[strt] == '\"')
// 	{
// 		c = s[strt];
// 		if (s[len] == c)
// 			strt += 1;
// 	}
// 	sub_s = (char *)malloc(len + 1);
// 	if (sub_s == NULL)
// 		//malloc_error
// 	ft_strlcpy(sub_s, s + strt, len + 1);
// 	return (sub_s);
// }

int	is_it_space(char *s, int i)
{
	if ((s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		return (0);
	return (1);
}

int ft_quotes(char *s, int i)
{
    char    quote;
	char	other_quote;

    quote = s[i];
	if (quote == 34)
		other_quote = 39;
	else
		other_quote = 34;
    i++;
    while (s[i] != '\0')
	{
		if (s[i] == quote)
		{
			if (s[i + 1] != '\0' && s[i + 1] != other_quote && is_it_space(s, i - 1) != 0)
			{
				while (s[i] != '\0' && s[i + 1] != other_quote && is_it_space(s, i) != 0)
					i++;
			}
		}
        	i++;
    if (s[i] == quote)
        return (i + 1);
    else
        return (-1);
	}
}
int ft_skip(char *s, int i)
{
    char    c;

    c = s[i];
    i++;
    while (s[i] != '\0' && s[i] != c)
        i++;
    if (s[i] == c)
        return (i + 1);
    else
        return (-1);
}

int w_count(char *s)
{
    int i;
    int words;

    i = 0;
    words = 0;
	while (s[i] != '\0')
	{
	    while (s[i] != '\0' && is_it_space(s, i) == 0)
            i++;
		if (s[i] != '\0' && is_it_space(s, i) != 0)
		{
			words++;
			while (s[i] != '\0' && is_it_space(s, i) != 0)
			{
				if (s[i] == '\'' || s[i] == '\"')
					i = ft_skip(s, i);
				if (i == -1)
					return (-1);
				i++;
			}
		}
	}
	return (words);
}

    while(s[i] != '\0')
    {
        while (s[i] != '\0' && is_it_space(s, i) == 0)
            i++;
        if (s[i] == '\'' || s[i] == '\"')
        {
			if (i - 1 > -1 && is_it_space(s, i) != 0)
				words--;
            i = ft_quotes(s, i);
            if (i == -1)
                return (-1);
        }
        else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
        {
            if (s[i] != '|' && (s[i + 1] == '>' || s[i + 1] == '<'))
                i++;
            i++;
        }
        else
        {
            while (s[i] != '\0' && ft_strchr(" >|<\'\"", s[i]) == NULL)
                i++;
        }
        words++;
    }
    return (words);
}

void    minishell_split(char *s, t_mini *line)
{
    int i;
    int j;
    int prev_i;

    i = 0;
    j = 0;
    while (s[i] != '\0')
    {
        while (s[i] != '\0' && s[i] == 32)
                i++;
        prev_i = i;
        if (s[i] == '\'' || s[i] == '\"')
            i = ft_skip(s, i);
        else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
        {
            if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>'))
                i++;
            i++;
        }
        else
        {
            while (s[i] != '\0' && ft_strchr(" >|<\'\"", s[i]) == NULL)
                i++;
        }
        if (prev_i != i)
        {
            line->metaed[j++] = ft_substr(s, prev_i, i - prev_i);
            if (line->metaed[j - 1] == NULL)
                printf("malloc error\n");
        }
    }
    line->metaed[j] = NULL;
}

// int ft_redirection(t_mini  *line, int i)
// {
//     int len;

//     len = ft_strlen(line->metaed[i]);
//     if (ft_strncmp(line->metaed[i], "<<", len) == 0)
//         printf("heredoc\n"); //discuss how to handle: here or before when taking in the args
// }

int is_it_redirect(char *s)
{
    int len;

    len = ft_strlen(s);
    if (ft_strncmp(s, "<", len) == 0 || ft_strncmp(s, ">", len) == 0 || \
        ft_strncmp(s, ">>", len) == 0 || ft_strncmp(s, "<<", len) == 0)
        return (0);
    return (-1);
}

void    validating(char *argv, t_mini *line)
{
    int words;
    int i;

    i = 0;
    words = w_count(argv);
    if (words == -1)
       printf("zsh: could not find the matching quote\n");
    line->metaed = (char **)malloc(sizeof(char *) * (words + 1));
    if (!line->metaed)
        printf("zsh: Cannot allocate memory\n");
    minishell_split(argv, line);
    if (ft_strncmp(line->metaed[0], "|", ft_strlen(line->metaed[0])) == 0)
        printf("zsh: parse error near `|'\n");
    while (i + 1 < words)
    {
        if (is_it_redirect(line->metaed[i]) == 0 && is_it_redirect(line->metaed[i + 1]) == 0)
           printf("zsh: parse error near i + 1\n"); //needs a function to output the second redirection
        i++;
    }
    if (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0 || \
        (is_it_redirect(line->metaed[i]) == 0))
        printf("zsh: parse error near \\n\n");
}

int    c_count(t_mini *line, t_alloc *ed, int i)
{

    ed->redir = 0;
    ed->other = 0;
    while (line->metaed[i] != NULL)
    {
		if (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
			break ;
        else if (is_it_redirect(line->metaed[i]) == 0)
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
	token->command = malloc(sizeof(char *) * (ed->other + 1));
	if (!token->command)
		return (-1);
	token->redirect = malloc(sizeof(char *) * (ed->redir + 1));
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
				printf("mallocfail 357\n");
            token->redirect[k++] = ft_strdup(line->metaed[pre_i++]);
			if (!(token->redirect[k - 1]))
				printf("mallocfail 360\n");
        }
        else
		{
            token->command[j++] = ft_strdup(line->metaed[pre_i++]);
			if (!(token->command[j - 1]))
				printf("mallocfail 366\n");
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
		if (line->metaed[i] != NULL && ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
			i++;
		j++;
	}
	j = 0;
	while (j < line->pipe_num)
	{
		i = 0;
		printf("j is %d\n", j);
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

int main(void)
{
    t_mini  line;
    // the actual line_read will replace the line_read
    char line_read[] = "<infile cat -e | cat -e > outfile > in > out option";

    line = (t_mini){0};
    validating(line_read, &line);
    // for checking the arguments, ie, will be deleted after
    int i = 0;
    while (line.metaed[i] != NULL)
        printf("%s\n", line.metaed[i++]);
	function (&line);
}