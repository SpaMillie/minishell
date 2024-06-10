#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*find_new_line(char *s, int part)
{
	int		i;
	int		n;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	ptr = s;
	n = ft_strlen(ptr) + 1;
	while (i < n)
	{
		if (s[i] == '\n')
		{
			i++;
			if (part == 0)
			{
				ptr = ft_strdup(s, 0);
				return (ptr);
			}
			ptr = &s[i];
			return (ft_strdup(ptr, 1));
		}
		i++;
	}
	return (NULL);
}

char	*get_buff(int fd, char **tempbuff)
{
	int		check;
	char	*buff;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (buff == NULL || fd < 0)
	{
		*tempbuff = free_str(tempbuff);
		return (free_str(&buff));
	}
	check = read(fd, buff, BUFFER_SIZE);
	if (check <= 0)
	{
		if (check == -1)
			*tempbuff = free_str(tempbuff);
		return (free_str(&buff));
	}
	buff[check] = '\0';
	return (buff);
}

char	*resolve_line(char **tempbuff, char **buff, int n)
{
	char	*temp;
	char	*line;

	if (n == 1)
	{
		line = find_new_line(*tempbuff, 0);
		if (!line)
			return (free_str(tempbuff));
		temp = ft_strdup(*tempbuff, 1);
		free_str(tempbuff);
		*tempbuff = find_new_line(temp, 1);
		free_str(&temp);
		return (line);
	}
	temp = ft_strdup(*buff, 0);
	line = ft_strjoin(tempbuff, &temp);
	if (!line)
		return (free_str(buff));
	*tempbuff = find_new_line(*buff, 1);
	free_str(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static char *buf[BUFFER_SIZE + 1];
	char	*line;
	char	*newline;
	int	countread;
	int	to_copy;

	line = ft_


	char		*line;
	char		*buff;

	line = NULL;
	if (ft_strchr(tempbuff, '\n') != NULL)
		return (resolve_line(&tempbuff, &buff, 1));
	buff = get_buff(fd, &tempbuff);
	while (buff != NULL)
	{
		if (ft_strchr(buff, '\n') != NULL)
			return (resolve_line(&tempbuff, &buff, 0));
		tempbuff = ft_strjoin(&tempbuff, &buff);
		if (!tempbuff)
			return (free_str(&buff));
		buff = get_buff(fd, &tempbuff);
	}
	if (tempbuff != NULL)
	{
		line = ft_strdup(tempbuff, 1);
		tempbuff = free_str(&tempbuff);
		return (line);
	}
	return (NULL);
}
