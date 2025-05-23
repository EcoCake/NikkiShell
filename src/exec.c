#include "../include/exec.h"
#include "../include/parse.h"

void	fill_token(t_token **tok)
{
	t_token	*node;
	t_token	*node2;

	node = malloc(sizeof(t_token));
	node2 = malloc(sizeof(t_token));
	node->value = "ls";
	node2->value = "-l";
	node->type = WORD;
	node2->type = WORD;
	*tok = node;
	node->next = node2;
}

void	create_nodes(t_comms **comms)
{
	t_comms *node;

	node = malloc(sizeof(t_comms));
	if (!node)
		return ;
	node->next = NULL;
	node->index = comms->index;
	if (!(*comms))
		*comms = node;
	else
	{
		*comms->next = node;
		*comms = *comms->next;
	}
}

void amount_pipes(t_token *tok, t_comms **comms)
{
	int i;

	i = 0;
	if (!tok->value[i])
		return ;
	while (tok)
	{
		if (tok->type == PIPE)
			comms->pipen++;
		create_nodes(comms);
		comms->index++;
		tok = tok->next;
	}

}

void	init_comms(t_comms **comms)
{
	comms->caf = NULL;
	comms->red_in = NULL;
	comms->red_out = NULL;
	comms->hlimiter = NULL;
	comms->next = NULL;
	comms->pipen = 0;
	comms->index = 0;
}

#include <stdio.h>
int main(int argc, char **argv)
{
	t_token *tok;
	t_comms *comms;

	init_comms(&comms);
	fill_token(&tok);
	amount_pipes(tok, &comms);
}