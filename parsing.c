#include <unistd.h>

typedef struct s_mini
{
    char **line;
}   t_mini;

int ch_count(char *s, t_mini *line)
{
    int i;
    int chunks;

    i = 0;
    chunks = 0;
    while(s[i] != '\0')
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            i = ft_skip(s, i)
        }
    }
}

int split_meta(char *argv, t_mini *line)
{
    int chunks;

    chunks = ch_count(argv, line);
}

int split(char *argv, t_mini *line)
{
    int check;

    check = split_meta(argv, line);
    if (check == -1)
        //heredoc
    split_words(line);
}


int main(char *line_read)
{
    t_mini  line;

    initialise(line);
    parse(line_read, &line);
}