/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:37:21 by tarini            #+#    #+#             */
/*   Updated: 2025/06/22 16:55:38 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

static int	get_cmd_parts_count(t_command *curr)
{
	int	i;

	i = 0;
	while (curr->cmd_parts && curr->cmd_parts[i])
		i++;
	return (i);
}

static t_arg	**extend_cmd_parts(t_arg **old_array, int old_size,
		t_arg *new_part)
{
	t_arg	**new_array;
	int		j;

	new_array = malloc(sizeof(t_arg *) * (old_size + 2));
	if (!new_array)
		return (NULL);
	j = 0;
	while (j < old_size)
	{
		new_array[j] = old_array[j];
		j++;
	}
	new_array[old_size] = new_part;
	new_array[old_size + 1] = NULL;
	free(old_array);
	return (new_array);
}

static int	ret_free_new_part(t_arg *new_part, char *expanded)
{
	if (new_part)
		free(new_part);
	if (expanded)
		free(expanded);
	return (RETURN_FAILURE);
}

/*
fonction qui :
- ajoute un nouveau token de type mot ou chaîne à la liste cmd_parts
	d’une commande ;
- alloue une nouvelle structure t_arg et y copie la valeur du token après
	duplication ;
- traite les quotes présentes dans le token pour marquer correctement la
	nouvelle partie ;
- crée un nouveau tableau t_arg* plus grand, copie l’ancien contenu, ajoute
	la nouvelle partie, termine par NULL ;
- libère l’ancien tableau cmd_parts et met à jour la commande avec le nouveau
	tableau ;
- retourne RETURN_SUCCESS si tout s’est bien passé, sinon RETURN_FAILURE en
	cas d’erreur d’allocation.
*/
int	process_word_string(t_token **tokens, t_command *curr, t_utils *utils)
{
	int		count;
	t_arg	*new_part;
	t_arg	**new_array;
	char	*expanded;

	new_part = malloc(sizeof(t_arg));
	if (!new_part)
		return (RETURN_FAILURE);
	process_quotes(*tokens, new_part);
	if (new_part->in_simple_quote)
		expanded = ft_strdup((*tokens)->value);
	else
		expanded = expand_variables((*tokens)->value, utils);
	if (!expanded)
		return (ret_free_new_part(new_part, expanded));
	new_part->arg = expanded;
	count = get_cmd_parts_count(curr);
	new_array = extend_cmd_parts(curr->cmd_parts, count, new_part);
	if (!new_array)
		return (ret_free_new_part(new_part, expanded));
	curr->cmd_parts = new_array;
	return (RETURN_SUCCESS);
}
