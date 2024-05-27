#include <stdio.h>
#include <stdlib.h>

/*char	*ft_strdup(const char *s1)
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
}*/

static char	*ft_edgecase(int n)
{
	if (!n)
		return (ft_strdup("0"));
	return (ft_strdup("-2147483648"));
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

char	*ft_itoa(int n)
{
	int		negative;
	int		len;
	char	*str;

	if (!n || n == -2147483648)
		return (ft_edgecase(n));
	negative = 0;
	if (n < 0)
	{
		n = -n;
		negative = 1;
	}
	len = ft_intlen(n);
	str = (char *)malloc(len + negative + 1);
	if (!str)
		return (NULL);
	if (negative == 1)
		str[0] = '-';
	str[len + negative] = '\0';
	while (n)
	{
		str[negative - 1 + len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
/*
int	main(void)
{
	char *s = ft_itoa(-40000007);

	printf("The number is %d, the string is %s", -40000007, s);
	free (s);
	return (0);
}*/
