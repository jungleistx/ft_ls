/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:28:37 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/25 13:59:51 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_node(t_node *node, int options)
{
	if (options & LONG)
	{
		ft_memdel((void**)&node->l_opt->owner);
		ft_memdel((void**)&node->l_opt->group);
		ft_memdel((void**)&node->l_opt);
		// free(node->l_opt->owner);
		// free(node->l_opt->group);
		// free(node->l_opt);
	}
	// printf("free node\t\t%s\n", node->name);
	ft_memdel((void**)&node->name);
	// printf("aaaa\n");
	node->next = NULL;
	ft_memdel((void**)&node);
}

void	free_file_nodes(t_node *head, int options)
{
	t_node	*tmp;
	t_node	*prev;
	t_node	*next;

	tmp = head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type != 4)
		{
			next = tmp->next;
			if (!prev)
				head = next;
			free_node(tmp, options);
			tmp = next;
			if (prev)
				prev->next = tmp;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	free_list(t_node **head, int options)
{
	t_node	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free_node(*head, options);
		*head = tmp;
	}
	*head = NULL;
}
// void	free_list(t_node *head, int options)
// {
// 	t_node	*tmp;

// 	while (head)
// 	{
// 		tmp = head->next;
// 		free_node(head, options);
// 		head = tmp;
// 	}
// 	head = NULL;
// }
