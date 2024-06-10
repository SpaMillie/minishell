#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include </usr/include/readline/readline.h>


typedef struct s_mini
{
    char	**metaed;
	char	**element;
    int		pipe_num;
}   t_mini;

char	**free_double(char **res)
{
	int	i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
	return (NULL);
}

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

char	*free_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s2);
	return (str);
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

int	is_it_space(char *s, int i)
{
	if ((s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		return (0);
	return (1);
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
				if ((line->element[i][j] == '>' && line->element[i][j + 1] == '>') || (line->element[i][j] == '<' && line->element[i][j + 1] == '<'))
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

int	second_split(t_mini *line)
{
	int	words;

	words = w_count(line);
	printf("words are %d\n", words);
	line->metaed = (char **)malloc(sizeof(char *) * (words + 1));
	if (!line->metaed)
    	printf("zsh: Cannot allocate memory\n");
	second_splitting(line);
	return (words);
}

int	first_split(char *argv, t_mini *line)
{
	int words;

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
	int	words;
	int	i;

    i = 0;
	if (first_split(argv, line) == -1)
		printf("zsh: could not find the matching quote\n");
	// i = 0;
    // while (line->element[i] != NULL)
    //     printf("%s\n", line->element[i++]);
	words = second_split(line);
	// i = 0;
    // while (line->metaed[i] != NULL)
    //     printf("%s\n", line->metaed[i++]);
    if (ft_strlen(line->metaed[i]) != 0 && ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
        printf("zsh: parse error near `|'\n");
    while (i + 1 < words)
    {
        if (ft_strlen(line->metaed[i]) != 0 && is_it_redirect(line->metaed[i]) == 0 && is_it_redirect(line->metaed[i + 1]) == 0)
           printf("zsh: parse error near i + 1\n"); //needs a function to output the second redirection
        i++;
    }
    if (ft_strlen(line->metaed[i]) != 0 && (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0 || \
        (is_it_redirect(line->metaed[i]) == 0)))
        printf("zsh: parse error near \\n\n");
}

char	*trim_copy(t_mini *line, char *copy, int i, int j)
{
	int		k;
	char	c;

	k = 0;
	c = line->metaed[i][j];
	while (k < j)
	{
		copy[k] = line->metaed[i][k];
		k++;
	}
	j++;
	while (line->metaed[i][j] != c)
	{
		if (c == '\'' && line->metaed[i][j] == '$')
		{
			copy[k++] = 7;
			j++;
		}
		else
			copy[k++] = line->metaed[i][j++];
	}
	j++;
	while (line->metaed[i][j] != '\0')
		copy[k++] = line->metaed[i][j++];
	copy[k] = '\0';
	free(line->metaed[i]);
	return (copy);
}

int	snip_snip(t_mini *line, int i, int j)
{
	char	*trimmed_string;
	int		len;
	char	c;
	int		count;

	len = ft_strlen(line->metaed[i]);
	c = line->metaed[i][j];
	count = j + 1;
	trimmed_string = malloc((sizeof(char)) * (len - 1));
	if (!trimmed_string)
		printf("malloc error\n");
	while (line->metaed[i][count] != c)
		count++;
	count = count - 1;
	printf("count is %d\n", count);
	line->metaed[i] = trim_copy(line, trimmed_string, i, j);
	return (count);
}

void	trim_quotes(t_mini *line)
{
	int	i;
	int	j;

	i = 0;
	while (line->metaed[i] != NULL)
	{
		j = 0;
		while (line->metaed[i][j] != '\0')
		{
			if (line->metaed[i][j] == '\'' || line->metaed[i][j] == '\"') 
				j = snip_snip(line, i, j);
			else
				j++;
		}
		printf("new metaed is %s\n", line->metaed[i]);
		i++;
	}
}

static int	ft_intlen(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putstr_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

char	*simple_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		printf("malloc fail\n");
	str[len--] = '\0';
	while (n)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char    *heredocing(char *delim, char *hd)
{
    int     fd;
    int     check;
	char	*line;

    check = 0;
	printf("entered heredocing\n");
	printf("delim is %s", delim);
    fd = open(hd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		printf("error while opening file\n");
	line = readline("heredoc>");
	while (ft_strncmp(delim, line, ft_strlen(delim)) != 0)
	{
		free (line);
		line = readline("heredoc>");
		printf("line is %s", line);
		if (line == NULL)
			break ;
		ft_putstr_fd(fd, line);
	}
    check = close(fd);
    if (check == -1)
        printf("error while closing file\n");
    free (delim);
	printf("exited heredocing\n");
    return (hd); //unlink heredocs in cleanup and close fds
}

void    here_doc(t_mini *line)
{
    int 	hd_num;
	int		i;
	char 	*hd_name;

    hd_num = 1;
	i = 0;
	printf("at least it came here\n");
    while (line->metaed[i] != NULL)
    {
        if (ft_strncmp(line->metaed[i], "<<", ft_strlen(line->metaed[i])) == 0)
        {
			printf("entered the loop\n");
			hd_name = free_strjoin(".here_", simple_itoa(hd_num), 2);
			printf("hd_name is %s\n", hd_name);
			//line->metaed[i + 1] can't be NULL and it can't be a meta which was checked before in validation (syntax errors) so no check is neccessary
            line->metaed[i + 1] = heredocing(line->metaed[i + 1], hd_name);
            hd_num++;
        }
        i++;
    }
}

int main(void)
{
    t_mini  line;
    // the actual line_read will replace the line_read
    char line_read[] = "cat << hat";

    line = (t_mini){0};
    validating(line_read, &line);
	trim_quotes(&line);
	here_doc(&line);
    // for checking the arguments, ie, will be deleted after
    int i = 0;
	while (line.metaed[i] != NULL)
		printf("%s\n", line.metaed[i++]);
	// function (&line);
	free_double(line.element);
	free_double(line.metaed);
}