

// line = 'echo '$HOME''

/*
single quotes just ft_skip + $ becomes 7
double quotes trickier
either way trim and then check if there are chars on either side and 
concat
 if [i == ' or "]
 if i != 0
 check if [i - 1] != space/pipe
 if i - 1 == space means all good
 if i - 1 == pipe means that basically i == 0
*/
int ft_single_q(char *str, t_mini *line, int i, int j)
{
    int     start;
    int     end;
    char    c;

    c = str[i];
    start = i;
    if (i - 1 > -1 && is_it_space(str, i - 1) != 0 && str[i - 1] != '|')
    {
        while(start - 1 > -1 && is_it_space(str, start - 1) != 0 && str[start - 1] != '|')
            start--;
    } 
    i++;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            break ;
        else if (str[i] == '\$' && str[i - 1] != '\\')
            str[i] = 7;
        i++; 
    }
    if (str[i] == '\0')
        return (-1);
    end = i;
    if (str[i + 1] != '\0' && is_it_space(str, i + 1) != 0)
    {
        i++;
        if (str[i] == '\'' || str[i] == '\"')
            i = ft_skip(str, i);
        while(str[i + 1] != '\0' && is_it_space(str, i + 1) != 0)
        {
            if (str[i])
        }
    }

    end = i;
}