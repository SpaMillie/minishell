
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

typedef struct s_list
{
    t_tokens token;
    int r_num;
    int o_num;
    struct s_list *next;
} t_list;

typedef struct s_mini
{
    char        **metaed;
    int         pipe_num;
    int         redir_num;
}   t_mini;

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t  ft_strlcpy(char	*dst, const char *src, size_t dstsize)
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

char	*ft_strchr(const char *s, int c)
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

char	*ft_strdup(const char *s1)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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

int ft_redirection(t_mini  *line, int i)
{
    int len;

    len = ft_strlen(line->metaed[i]);
    if (ft_strncmp(line->metaed[i], "<<", len) == 0)
        printf("heredoc\n"); //discuss how to handle: here or before when taking in the args
}

//check if works
void    c_count(t_mini *line, t_list *node, int i)
{

    node->r_num = 0;
    node->o_num = 0;
    while (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) != 0 \
        || line->metaed[i] != NULL)
    {
        if (is_it_redirect(line->metaed[i]) == 0)
        {
            node->r_num += 2;
            i++;
        }
        else
            node->o_num++;
        i++;
    }
}

int is_it_redirect(char *s)
{
    int len;

    len = ft_strlen(s);
    if (ft_strncmp(s, "<", len) == 0 || ft_strncmp(s, ">", len) == 0 || \
        ft_strncmp(s, ">>", len) == 0 || ft_strncmp(s, "<<", len) == 0)
        return (0);
    return (-1);
}
int alloc_token(t_list *head, t_mini *line)
{
    head->token
}

int    createnode(t_list *head, t_mini *line, int i)
{
    c_count(line, head, i);
    alloc_token(head, line)
    
    ->token->r_num = c_count(line, i);
    token->redirect[j] = 
    while (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) != 0 \
        || line->metaed[i] != NULL)
    {
        
        i++;
    }
    return (i);
}


void    sort_args(t_mini *line, t_list *head)
{
    int i;

    p_count(line, "|");
    head = malloc(sizeof(t_list));
    if (!head)
        printf("malloc failed\n");
    i = createnode(head, line, 0);

    while (line->pipe_num > 0)
    {
        ft_node(head, line, i);
        line->pipe_num--;
    }

    int i;
    int len;
    int check;

    i = 0;
    check = 0;
    p_count(line);
    allocate_commands(line, )
    while (line->metaed[i] != NULL)
    {
        while (line->pipe_num != 0)
        {
            
        len = ft_strlen(line->metaed[i]);
        if (ft_strncmp(line->metaed[i], "|", len) == 0)
            line->pipe_num--;
        else if (is_it_redirect(line->metaed[i]) == 0)
            check = ft_redirection(line, i); //needs to become i if not -1
        else
            check = ft_save(line, len, i); //needs to be 0 if not -1
        if (check == -1)
            printf("malloc error\n"); //needs to exit and clean
        else if (check > 0)
            i = check;
        i++;
        }
    }
}

