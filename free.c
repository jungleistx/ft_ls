/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:28:37 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/18 13:54:43 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_node(t_node *node, int options)
{
	if (options & LONG && node->type != 0)
	{
		if (node->type == 10)
			ft_memdel((void**)&node->l_opt->sym_link);
		ft_memdel((void**)&node->l_opt->owner);
		ft_memdel((void**)&node->l_opt->group);
		ft_memdel((void**)&node->l_opt);
	}
	ft_memdel((void**)&node->path);
	ft_memdel((void**)&node->name);
	node->next = NULL;
	ft_memdel((void**)&node);
}

void	free_file_nodes(t_node **head, int options)
{
	t_node	*tmp;
	t_node	*prev;
	t_node	*next;

	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type != 4 && tmp->type != 1)
		{
			next = tmp->next;
			if (!prev)
				*head = next;
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

void	free_non_dir_nodes(t_node **head, int options)
{
	t_node	*tmp;
	t_node	*prev;
	t_node	*next;

	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type != 4)
		{
			next = tmp->next;
			if (!prev)
				*head = next;
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
