/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:36:53 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 12:42:18 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Fonction qui :
- analyse le type de quotes du token donné ;
- met à jour les drapeaux dans cmd_part pour indiquer si le contenu est entre simples ou doubles quotes ;
- si aucune quote n’est présente, réinitialise les drapeaux à false.
*/
void process_quotes(t_token *token, t_arg *cmd_part)
{
	if (token->type == TOK_SINGLE_QUOTES)
	{
		cmd_part->in_simple_quote = true;
		cmd_part->in_double_quote = false;
	}
	else if (token->type == TOK_DOUBLE_QUOTES)
	{
		cmd_part->in_simple_quote = false;
		cmd_part->in_double_quote = true;
	}
	else
	{
		cmd_part->in_simple_quote = false;
		cmd_part->in_double_quote = false;
	}
}
