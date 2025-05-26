

char *ft_strdup(const char *str)
{
	char	*w;
	int		len;

	len = 0;
	while(str[len])
		len++;
	w = malloc(len + 1);
	w[len] = '\0';
	len = 0;
	while (str[len])
		w[len] = str[len++];
	return (w);
}
