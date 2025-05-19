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

void amount_pipes(t_token *tok)
{
	int i;
	t_comms *comms;

	comms->pipen = 0;
	i = 0;
	if (!tok->value[i])
		return ;
	while (tok)
	{
		if (tok->type == PIPE)
			comms->pipen++;
		tok = tok->next;
	}

}

#include <stdio.h>
int main(int argc, char **argv)
{
	t_token *tok;

	fill_token(&tok);
	amount_pipes(tok);
}