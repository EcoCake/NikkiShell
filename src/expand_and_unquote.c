/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_unquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:34:34 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 17:57:15 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_char(char **final_str, t_exp_ctx *ctx)
{
	char	temp_str[2];
	char	*var_value;
	int		var_len;

	if (ctx->str[ctx->i] == '$' && !ctx->in_squote)
	{
		var_len = get_var_name_len(&ctx->str[ctx->i + 1]);
		var_value = expand_variable(&ctx->str[ctx->i + 1], ctx->env, ctx->las);
		if (!var_value)
			return (0);
		*final_str = str_append(*final_str, var_value);
		free(var_value);
		ctx->i += var_len + 1;
	}
	else
	{
		temp_str[0] = ctx->str[ctx->i];
		temp_str[1] = '\0';
		*final_str = str_append(*final_str, temp_str);
		ctx->i++;
	}
	if (!*final_str)
		return (0);
	return (1);
}

int	handle_quotes(t_exp_ctx *ctx)
{
	if (ctx->str[ctx->i] == '\'' && !ctx->in_dquote)
	{
		ctx->in_squote = !ctx->in_squote;
		ctx->i++;
		return (1);
	}
	if (ctx->str[ctx->i] == '"' && !ctx->in_squote)
	{
		ctx->in_dquote = !ctx->in_dquote;
		ctx->i++;
		return (1);
	}
	if (ctx->str[ctx->i] == '$' && ctx->str[ctx->i + 1]
		== '"' && !ctx->in_squote)
	{
		ctx->i++;
		return (1);
	}
	return (0);
}

char	*expand_and_unquote(char *str, t_env_var *env_list, int las)
{
	char		*final_str;
	t_exp_ctx	ctx;

	if (!str)
		return (NULL);
	final_str = ft_strdup("");
	if (!final_str)
		return (NULL);
	ctx.str = str;
	ctx.env = env_list;
	ctx.las = las;
	ctx.i = 0;
	ctx.in_squote = 0;
	ctx.in_dquote = 0;
	while (ctx.str[ctx.i])
	{
		if (handle_quotes(&ctx))
			continue ;
		if (!process_char(&final_str, &ctx))
		{
			free(final_str);
			return (NULL);
		}
	}
	return (final_str);
}
