
char    *resolve_heredoc(char *denom, int hd)
{
    //use the pipe and dup2
    int         fd;
    int         check;
    char    *here_d;
    const char  arg[256];

    check = 0;
    here_d = ft_itoa(hd);
    fd = open(here_d, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        printf("error while opening file\n");
    check = (fd, STDOUT_FILENO);
    if (check == -1)
        printf("error while dup2ing\n");
    arg = readline(fd);
    check = close (fd);
    if (check == -1)
        printf("error while closing file\n");
    check = unlink("./here_doc");
    if (check == -1)
        printf("error while removing file\n");
    free (denom);
    return (here_d);
}

void    here_doc(t_mini *line)
{
    int i = 0;
    int hd_num;

    hd_num = 0;
    while (line->metaed[i] != NULL)
    {
        if (ft_strncmp(line->metaed[i], "<<", ft_strlen(line->metaed[i]) == 0))
        {
            line->metaed[i + 1] = resolve_heredoc(line->metaed[i + 1], hd_num);
            hd_num++;
        }
        i++;
    }
}