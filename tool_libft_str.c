#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ext;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (!(ext = malloc(len + 1)))
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		ext[i] = s[start + i];
		i++;
	}
	ext[i] = '\0';
	return (ext);
}

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*cp;

	if (!(cp = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	size = 0;
	while (s1[size])
	{
		cp[size] = s1[size];
		size++;
	}
	cp[size] = '\0';
	return (cp);
}

size_t		ft_strlcat(char *restrict dst, const char *restrict src,
		size_t dstsize)
{
	int	i;
	int	lendst;

	lendst = 0;
	while (*dst)
	{
		lendst++;
		dst++;
	}
	i = 0;
	while (src[i] && i < (int)dstsize - lendst - 1)
	{
		*dst = src[i];
		dst++;
		i++;
	}
	*dst = '\0';
	if ((int)dstsize > lendst)
		return (ft_strlen(src) + lendst);
	else
		return (ft_strlen(src) + dstsize);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	t1;
	size_t	t2;

	t1 = 0;
	t2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(a = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[t1])
	{
		a[t1] = s1[t1];
		t1++;
	}
	while (s2[t2])
	{
		a[t1 + t2] = s2[t2];
		t2++;
	}
	a[t1 + t2] = '\0';
	return (a);
}