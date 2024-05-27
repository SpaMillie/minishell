/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:48:57 by mspasic           #+#    #+#             */
/*   Updated: 2024/05/27 11:50:15 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// #define TRUE 1
// #define FALSE 0

//most printf's should be exits

typedef struct s_tokens
{
    char    **cmnd;
    char    **redirect;
    char    **file_name;
}   t_tokens;

typedef struct s_mini
{
    char        **metaed;
    int         pipe_num;
}   t_mini;


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

int w_count(char *s)
{
    int i;
    int words;

    i = 0;
    words = 0;
    while(s[i] != '\0')
    {
        while (s[i] != '\0' && s[i] == 32) //add whitespace cchars
            i++;
        if (s[i] == '\'' || s[i] == '\"')
        {
            i = ft_skip(s, i);
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
//     // line->token->redirect
//     while (line->metaed[i] != NULL)
//     {
//         if (line->metaed[i][0] == '|')
//             line->pipe_num++;
//         i++;
//     }
//     return (line->pipe_num);
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


// void    sort_args(t_mini *line)
// {
//     int i;
//     int len;
//     int check;

//     i = 0;
//     check = 0;
//     while (line->metaed[i] != NULL)
//     {
//         len = ft_strlen(line->metaed[i]);
//         if (ft_strncmp(line->metaed[i], "|", len) == 0)
//         {
//             if (i == 0)
//                 printf("zsh: parse error near '|'\n"); //exit_error; discuss: echo | echo, echo | ; the 2nd example asks for a command (pipe>)
//             line->pipe_num++;
//         }
//         else if (is_it_redirect(line->metaed[i]) == 0)
//             check = ft_redirection(line, i); //needs to become i if not -1
//         else
//             check = ft_save(line, len, i); //needs to be 0 if not -1
//         if (check == -1)
//             printf("malloc error\n"); //needs to exit and clean
//         else if (check > 0)
//             i = check;
//         i++;
//     }
// }

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
    i--;
    if (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0 || \
        (is_it_redirect(line->metaed[i]) == 0))
        printf("zsh: parse error near \\n\n");
}

int main(void)
{
    t_mini  line;
    // the actual line_read will replace the line_read
    char line_read[] = "heyheyhey < cart > > hayr | vcat gfgf | eufh | <<";

    line = (t_mini){0};
    validating(line_read, &line);
    // for checking the arguments, ie, will be deleted after
    int i = 0;
    while (line.metaed[i] != NULL)
        printf("%s\n", line.metaed[i++]);
}