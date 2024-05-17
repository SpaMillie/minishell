
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// #define TRUE 1
// #define FALSE 0

typedef struct s_mini
{
    char **metaed;
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

int ch_count(char *s)
{
    int i;
    int chunks;

    i = 0;
    printf("entered chcount\n");
    chunks = 0;
    while(s[i] != '\0')
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            i = ft_skip(s, i);
            if (i == -1)
                return (-1);
        }
        else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
            i++;
        else
        {
            while (s[i] != '\0' && s[i] != '|' && s[i] != '>' && s[i] != '<' && \
                s[i] != '\'' && s[i] != '\"')
                i++;
        }
        chunks++;
    }
    printf("exited chcount\n");
    return (chunks);
}

void    split_meta(char *s, t_mini *line)
{
    int i;
    int j;
    int prev_i;

    printf("entered splitmeta\n");
    i = 0;
    j = 0;
    while (s[i] != '\0')
    {
        prev_i = i;
        if (s && (s[i] == '\'' || s[i] == '\"'))
            i = ft_skip(s, i);
        else if (s[i] != '\0'  && (s[i] == '|' || s[i] == '>' || s[i] == '<'))
            i++;
        else
        {
            while (s[i] != '\0' && ft_strchr(">|<\'\"", s[i]) == NULL)
                i++;
        }
        if (prev_i != i)
        {
            printf("i is %d, prev is %d\n", i, prev_i);
            line->metaed[j++] = ft_substr(s, prev_i, i - prev_i);
            if (line->metaed[j - 1] == NULL)
                printf("malloc error\n");
        }
    }
    line->metaed[j] = NULL;
    printf("exited splitmeta\n");
}

int first_split(char *argv, t_mini *line)
{
    int chunks;

    printf("entered firstsplit\n");
    chunks = ch_count(argv);
    line->metaed = (char **)malloc(sizeof(chunks + 1));
    if (!line->metaed)
        return (-1); //malloc_error
    split_meta(argv, line);
    printf("exited firstsplit\n");
    return (0);
}

void parse(char *argv, t_mini *line)
{
    int check;
    printf("entered parse\n");
    check = first_split(argv, line);
    if (check == -1)
        printf("error\n");
    // split_words(line);
    printf("exited parse\n");
}

int main(void)
{
    t_mini  line;
    char line_read[] = "< infile echo 'hey' hoe what |cat > out";

    // initialise(line);
    line = (t_mini){0};
    printf("%s\n", line_read);
    parse(line_read, &line);
    int i = 0;
    while (line.metaed[i] != NULL)
        printf("%s\n", line.metaed[i++]);
}
