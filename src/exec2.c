#include "../include/exec.h"
#include "../include/parse.h"

t_comms	*find_last(t_comms *comms)
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
	init_node(node);
	if (*comms)
	{
		find_last(*comms)->next = node;
		node->index = find_last(*comms)->index + 1;
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
		node->red_in = ft_strdup(token->value);
	}
	if (token->type == REDIR_OUT_W)
	{
		node->red_out = ft_strdup(token->value);
	}
	if (token->type == HERE_DOC)
	{
		node->hlimiter = ft_strdup(token->value);
	}
	if (token->type == WORD)
	{
		node->caf[node->caf_num++] = ft_strdup(token->value);
	}
}

void put(t_comms **comms, t_token **token)
{
	t_token **finger1;

	finger1 = token;
	create_node(comms);
	while (finger1)
	{
		if (*finger1->value[0] == '|')
		{
			*finger1 = (*finger1)->next;
			create_node(comms);
			comms = comms->next;
		}
		fill_node(*comms, *token);
		*finger1 = (*finger1)->next;
	}
}
