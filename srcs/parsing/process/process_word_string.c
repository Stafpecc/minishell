/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:37:21 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 12:56:17 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

/*
fonction qui :
- ajoute un nouveau token de type mot ou chaîne à la liste cmd_parts d’une commande ;
- alloue une nouvelle structure t_arg et y copie la valeur du token après duplication ;
- traite les quotes présentes dans le token pour marquer correctement la nouvelle partie ;
- crée un nouveau tableau t_arg* plus grand, copie l’ancien contenu, ajoute la nouvelle partie, termine par NULL ;
- libère l’ancien tableau cmd_parts et met à jour la commande avec le nouveau tableau ;
- retourne RETURN_SUCCESS si tout s’est bien passé, sinon RETURN_FAILURE en cas d’erreur d’allocation.
*/
int process_word_string(t_token **tokens, t_command *curr)
{
	t_arg *new_part;
	int i;
	int j;
	t_arg **new_array;

	i = 0;
	while (curr->cmd_parts && curr->cmd_parts[i])
		i++;
	new_part = malloc(sizeof(t_arg));
	if (!new_part)
		return (RETURN_FAILURE);
	new_part->arg = ft_strdup((*tokens)->value);
	if (!new_part->arg)
	{
		free(new_part);
		return (RETURN_FAILURE);
	}
	process_quotes(*tokens, new_part);
	new_array = malloc(sizeof(t_arg *) * (i + 2));
	if (!new_array)
	{
		free(new_part->arg);
		free(new_part);
		return (RETURN_FAILURE);
	}
	j = 0;
	while (j < i)
	{
		new_array[j] = curr->cmd_parts[j];
		j++;
	}
	new_array[i] = new_part;
	new_array[i + 1] = NULL;
	free(curr->cmd_parts);
	curr->cmd_parts = new_array;
	return (RETURN_SUCCESS);
}
