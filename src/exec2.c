t_comms	find_last(t_comms *comms)
{
	if (!comms)
		return (NULL);
	while (comms->next)
		comms = comms->next;
	return (comms);
}

void	create_node(t_comms **comms)
{
	t_comms *node;
	
	node = malloc(sizeof(t_comms));
	if (!node)
		return ;
	node->next = NULL;
	node->index = 0;
	if (*comms)
	{
		find_last(*comms)->next = node;
		node->index++;
	}
	else
		*comms = node;
}

void fill_node(t_comms *node, t_token *token)
{
	if (!node || !token)
		return ;
	if (token->value == NULL || token->value[0] == '\0')
		return ;
	if (token->type == REDIR_IN_W)
	{
		node->red_in = token->value;
	}
}

void put(t_comms **comms, t_token **token)
{
	t_token **finger1;
	t_comms	new_node;

	finger1 = token;

	while (finger1)
	{
		new_node = create_node(**comms);
		fill_node(**comms, **token);
		finger1 = finger1->next;
	}
}
