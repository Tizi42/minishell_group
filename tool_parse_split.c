#include "minishell.h"

char		**jump_quotes_ft_split(char const *s, char *quoted, char c)
{
	char		**tabs;
	int			count[3];

	ft_memset(count, 0, sizeof(count));
	if (s == NULL || !(tabs = malloc(sizeof(char *) * (sizec(s, c) + 2))))
		return (NULL);
	count[0] = -1;
	while (s[count[1]])
	{
		if ((s[count[1]] == c && quoted[count[1]] == NQ) || s[count[1] + 1] == '\0')
		{
			if (s[count[1] + 1] == '\0' && s[count[1]] != c)
				count[1]++;
			if (count[1] - count[0] != 1)
			{
				if (!(docp(tabs, s, count)))
					return (NULL);
			}
			count[0] = count[1];
		}
		if (s[count[1]])
			count[1]++;
	}
	tabs[count[2]] = NULL;
	return (tabs);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*rep;

	rep = b;
	i = 0;
	while (i < len)
	{
		rep[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int	docp(char **tabs, char const *s, int *ct)
{
	int i;

	if (!(tabs[ct[2]] = malloc(sizeof(char) * (ct[1] - ct[0]))))
		return (0);
	i = 0;
	while (ct[0] + 1 + i < ct[1])
	{
		tabs[ct[2]][i] = s[ct[0] + 1 + i];
		i++;
	}
	tabs[ct[2]][i] = '\0';
	ct[2]++;
	return (1);
}

int	sizec(char const *s, char c)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}
