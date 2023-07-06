#include "../includes/minishell.h"

t_list_token	*ft_newlst_token(char *word)
{
	t_list_token	*new;
	
	new = malloc(sizeof(t_list_cmd));
	if (!new)
		return (NULL);
	new->word = word;
	new->type = /* Function to get token type */
	new->red = /* Function to get token redirection */
	new->quote = /* Function to get token quote */
	new->next = NULL;
	new->prev = NULL;
}