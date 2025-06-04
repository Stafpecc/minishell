/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:37 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 12:41:46 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Fonction qui :
- crée une nouvelle commande et la lie à la commande courante via le champ next ;
- met à jour le pointeur courant pour pointer sur cette nouvelle commande ;
- retourne RETURN_SUCCESS si la création réussit, sinon libère la mémoire et retourne une erreur.
*/
int process_pipe(t_command **curr, t_command *head)
{
	(*curr)->next = create_command();
	if (!(*curr)->next)
		return (process_free_exit(head));
	(*curr) = (*curr)->next;
	return (RETURN_SUCCESS);
}