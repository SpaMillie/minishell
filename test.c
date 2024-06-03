#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


typedef struct s_mini
{
    char	**metaed;
	char	**element;
    int		pipe_num;
}   t_mini;

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

int	is_it_space(char *s, int i)
{
	if ((s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		return (0);
	return (1);
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
void	second_splitting(t_mini *line)
{
	int	prev_j;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (line->element[i] != NULL)
	{
		j = 0;
		while (line->element[i][j] != '\0')
		{
			prev_j = j;
			if (line->element[i][j] == '>' || line->element[i][j] == '<' || line->element[i][j] == '|')
			{
				if ((line->element[i][j] == '>' && line->element[i][j + 1] == '>') || (line->element[i][j] == '<' &&  line->element[i][j + 1] == '<'))
					j++;
				j++;
			}
			else
			{
				while (line->element[i][j] != '\0' && line->element[i][j] != '>' && line->element[i][j] != '<' && line->element[i][j] != '|')
				{
					if (line->element[i][j] == '\'' || line->element[i][j] == '\"')
						j = ft_skip(line->element[i], j);
					else
						j++;
				}
			}
			line->metaed[k++] = ft_substr(line->element[i], prev_j, j - prev_j);
		    if (line->metaed[k - 1] == NULL)
                printf("malloc error\n");
		}
		i++;	
	}
	line->metaed[k] = NULL;
}


void	first_splitting(char *s, t_mini *line)
{
    int	j;
	int i;
    int prev_i;

    i = 0;
	j = 0;
	while (s[i] != '\0')
	{
	    while (s[i] != '\0' && is_it_space(s, i) == 0)
            i++;
		if (s[i] != '\0' && is_it_space(s, i) != 0)
		{
			prev_i = i;
			while (s[i] != '\0' && is_it_space(s, i) != 0)
			{
				if (s[i] == '\'' || s[i] == '\"')
					i = ft_skip(s, i);
				else
					i++;
			}
            line->element[j++] = ft_substr(s, prev_i, i - prev_i);
            if (line->element[j - 1] == NULL)
                printf("malloc error\n");
		}
	}
	line->element[j] = NULL;
}

int e_count(char *s)
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
				else
					i++;
				if (i == -1)
					return (-1);
			}
		}
	}
	return (words);
}

int	w_count(t_mini *line)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	words = 0;
	while (line->element[i] != NULL)
	{
		j = 0;
		while (line->element[i][j] != '\0')
		{
			if (line->element[i][j] == '>' || line->element[i][j] == '<' || line->element[i][j] == '|')
			{
				if ((line->element[i][j] == '>' && line->element[i][j + 1] == '>') || (line->element[i][j] == '<' &&  line->element[i][j + 1] == '<'))
					j++;
				j++;
				words++;
			}
			else
			{
				while (line->element[i][j] != '\0' && line->element[i][j] != '>' && line->element[i][j] != '<' && line->element[i][j] != '|')
				{
					if (line->element[i][j] == '\'' || line->element[i][j] == '\"')
						j = ft_skip(line->element[i], j);
					else
						j++;
				}
				words++;
			}
		}
		i++;
	}
	return (words);
}

void	second_split(t_mini *line)
{
	int	i;
	int	words;

	i = 0;
	words = w_count(line);
	printf("words are %d\n", words);
	line->metaed = (char **)malloc(sizeof(char *) * (words + 1));
    if (!line->metaed)
        printf("zsh: Cannot allocate memory\n");
	second_splitting(line);
}

int	first_split(char *argv, t_mini *line)
{
	int words;
    int i;

    i = 0;
    words = e_count(argv);
    if (words == -1)
		return (-1); //printf("zsh: could not find the matching quote\n");
	printf("elements = %d\n", words);
    line->element = (char **)malloc(sizeof(char *) * (words + 1));
    if (!line->element)
        printf("zsh: Cannot allocate memory\n");
    first_splitting(argv, line);
	return (0);
}

void    validating(char *argv, t_mini *line)
{
	if (first_split(argv, line) == -1)
		printf("zsh: could not find the matching quote\n");
	int i = 0;
    while (line->element[i] != NULL)
        printf("%s\n", line->element[i++]);
	second_split(line);
	i = 0;
    while (line->metaed[i] != NULL)
        printf("%s\n", line->metaed[i++]);
    // if (ft_strncmp(line->metaed[0], "|", ft_strlen(line->metaed[0])) == 0)
    //     printf("zsh: parse error near `|'\n");
    // while (i + 1 < words)
    // {
    //     if (is_it_redirect(line->metaed[i]) == 0 && is_it_redirect(line->metaed[i + 1]) == 0)
    //        printf("zsh: parse error near i + 1\n"); //needs a function to output the second redirection
    //     i++;
    // }
    // if (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0 || \
    //     (is_it_redirect(line->metaed[i]) == 0))
    //     printf("zsh: parse error near \\n\n");
}

int main(void)
{
    t_mini  line;
    // the actual line_read will replace the line_read
    char line_read[] = "'echo ' 'hey'>>hom|ed";

    line = (t_mini){0};
    validating(line_read, &line);
    // for checking the arguments, ie, will be deleted after
    // int i = 0;
    // while (line.metaed[i] != NULL)
    //     printf("%s\n", line.metaed[i++]);
	// function (&line);
}