/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:34:25 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 15:38:28 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

/*
Fonction qui :
- avance au token suivant après une redirection d’entrée (<) ;
- vérifie que ce token est un mot valide, sinon affiche une erreur de syntaxe ;
- alloue ou utilise le tableau redirect_in pour stocker l’argument de la redirection à la position statique location_of_the_table ;
- copie l’argument, traite les quotes, ajoute l’argument à cmd_parts, marque le dernier argument comme final ;
- avance le token et incrémente location_of_the_table ;
- retourne RETURN_SUCCESS ou libère et retourne une erreur en cas d’échec.
*/
int process_redirect_in(t_token **tokens, t_command *curr, t_command *head, t_utils *utils)
{
	int i;
	static int location_of_the_table = 0;

	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		if (*tokens && !is_redirect_or_pipe(*tokens))
			print_syntax_error((*tokens)->value, utils);
		else
			print_syntax_error("newline", utils);
		return (process_free_exit(head));
	}
	if (!curr->redirect_in)
	{
		curr->redirect_in = malloc(sizeof(t_arg));
		if (!curr->redirect_in)
			return (process_free_exit(head));
	}
	curr->redirect_in[location_of_the_table]->arg = ft_strdup((*tokens)->value);
	if (!curr->redirect_in[location_of_the_table]->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->redirect_in[location_of_the_table]);
	curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	i = 0;
	while (curr->cmd_parts[i] != NULL)
		i++;
	curr->cmd_parts[i - 1]->final = true;
	(*tokens) = (*tokens)->next;
	location_of_the_table++;
	return (RETURN_SUCCESS);
}


/*
Fonction qui :
- avance au token suivant après une redirection de sortie (>) ;
- vérifie la validité du token, affiche une erreur si nécessaire ;
- alloue ou utilise le tableau redirect_out avec un index statique location_of_the_table pour stocker l’argument ;
- copie l’argument, traite les quotes, ajoute à cmd_parts, marque le dernier argument comme final ;
- incrémente location_of_the_table et retourne RETURN_SUCCESS ou erreur en cas de problème.
*/
int process_redirect_out(t_token **tokens, t_command *curr, t_command *head, t_utils *utils)
{
	int i;
	static int location_of_the_table = 0;
	
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		if (*tokens && !is_redirect_or_pipe(*tokens))
			print_syntax_error((*tokens)->value, utils);
		else
			print_syntax_error("newline", utils);
		return (process_free_exit(head));
	}
	if (!curr->redirect_out)
	{
		ft_printfd("ici?????\n\n\n");
		//curr->redirect_out = malloc(sizeof(t_arg));
		if (!curr->redirect_out)
			return (process_free_exit(head));
	}
	curr->redirect_out[location_of_the_table]->arg = ft_strdup((*tokens)->value);
	if (!curr->redirect_out[location_of_the_table]->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->redirect_out[location_of_the_table]);
	curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	i = 0;
	while (curr->cmd_parts[i] != NULL)
		i++;
	curr->cmd_parts[i - 1]->final = true;
	location_of_the_table++;
	return (RETURN_SUCCESS);
}

/*
Fonction qui :
- avance au token suivant après une redirection append (>>) ;
- vérifie que le token suivant est valide, sinon affiche une erreur ;
- alloue append_redirections si besoin, copie l’argument et traite les quotes ;
- ajoute l’argument à cmd_parts, marque le dernier argument comme final ;
- avance le token et retourne RETURN_SUCCESS ou une erreur si un problème survient.
*/
int process_append_redirect(t_token **tokens, t_command *curr, t_command *head, t_utils *utils)
{
	int i;

	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		if (*tokens && !is_redirect_or_pipe(*tokens))
			print_syntax_error((*tokens)->value, utils);
		else
			print_syntax_error("newline", utils);
		return (process_free_exit(head));
	}
	if (!curr->append_redirections)
	{
		curr->append_redirections = malloc(sizeof(t_arg));
		if (!curr->append_redirections)
			return (process_free_exit(head));
	}
	curr->append_redirections->arg = ft_strdup((*tokens)->value);
	if (!curr->append_redirections->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->append_redirections);
	curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	i = 0;
	while (curr->cmd_parts[i] != NULL)
		i++;
	curr->cmd_parts[i - 1]->final = true;
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}

/*{a fix} : se renseigner sur la gestion des redirections append (>>) et envisager 
de stocker les append_redirections dans un tableau, comme redirect_in et redirect_out, 
pour uniformiser le traitement et permettre la gestion de plusieurs append.*/
