// // #include "../includes/minishell.h"

// t_tok	*ft_newlst_token(char *word)
// {
// 	t_tok	*new;

// 	new = malloc(sizeof(t_tok));
// 	if (!new)
// 		return (NULL);
// 	new->word = word;
// 	new->type = ft_get_tk_type(word);
// 	new->red = ft_red_type(word);
// 	new->quote = ft_get_quoted_tk(word);
// 	new->next = NULL;
// 	new->prev = NULL;
// }

// void	ft_lstadd_back_token(t_tok **lst, t_tok *nw)
// {
// 	t_tok	*node;


// // void	ft_lstadd_back_token(t_list_token **lst, t_list_token *nw)
// // {
// // 	t_list_token	*node;

// // 	node = *lst;
// // 	if (node == NULL)
// // 		node = nw;
// // 	else
// // 	{
// // 		while (node->next != NULL)
// // 			node = node->next;
// // 		node->next = nw;
// // 		nw->prev = node;
// // 	}
// // }