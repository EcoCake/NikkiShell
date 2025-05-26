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

void	init_node(t_comms *node)
{
	node->caf = NULL;
	node->red_in = NULL;
	node->red_out = NULL;
	node->hlimiter = NULL;
	node->next = NULL;
	node->pipen = 0;
	node->caf_num = 0;
}

#include <stdio.h>
int main(int argc, char **argv)
{
	t_token *tok;
	t_comms *comms;

	comms = NULL;
	comms->index = 0;
	comms->pipen = 0;
	fill_token(&tok);
	amount_pipes(tok, &comms);
}