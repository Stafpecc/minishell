/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:34:09 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 12:27:08 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

/*Fonction qui :
- vérifie si une commande est vide ou invalide ;
- regarde si la structure est nulle, si le tableau de parties est vide,
  	ou si la première partie (la commande elle-même) est absente ;
- retourne true si rien n’est exécutable, false sinon.*/
bool	is_empty_command(t_command *cmd)
{
	return (!cmd || !cmd->cmd_parts || !cmd->cmd_parts[0]);
}

/*Fonction qui :
- s’utilise quand une erreur de syntaxe est rencontrée dans les redirections ou les tokens ;
- affiche un message d’erreur clair à l’utilisateur ;
- retourne une valeur d’échec standard pour stopper ou ignorer la commande.*/
int	return_failure(const char *token, t_utils *utils)
{
	print_syntax_error(token, utils);
	return (RETURN_FAILURE);	
}

/*Fonction qui :
- affiche un message d’erreur avec le token problématique (>, <, etc.) ;
- met à jour le code de retour global avec une erreur de syntaxe ;
- sert à indiquer qu’un token inattendu a été trouvé pendant le parsing.*/
void print_syntax_error(const char *token, t_utils *utils)
{
	utils->last_return = CMD_INVALID_ARGUMENT;
	ft_printfd("minishell: syntax error near unexpected token `%s'\n", token);
}
