/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:50:21 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/25 23:50:18 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	update_list_time(t_node *prev, t_node *node, t_node **head, int *sort)
{
	t_node	*tmp;

	(*sort)++;
	if (prev)
		prev->next = node->next;
	else
		*head = node->next;
	prev = node->next;
	tmp = node->next->next;
	node->next->next = node;
	node->next = tmp;
}

//	first node is smallest number (newest)
void	list_sort_time_reverse(t_node **head)
{
	t_node	*tmp;
	t_node	*prev;
	int		sorted;

	sorted = 0;
	while (!sorted)
	{
		tmp = *head;
		while (tmp && tmp->next)
		{
			if (tmp->sec > tmp->next->sec && tmp->n_sec > tmp->next->n_sec)
				update_list_time(prev, tmp, head, &sorted);
			else if (tmp->sec == tmp->next->sec && tmp->n_sec ==
				tmp->next->n_sec && tmp->name < tmp->next->name)
				update_list_time(prev, tmp, head, &sorted);
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
		if (sorted == 0)
			return ;
		sorted = 0;
	}
}

// first node is biggest number (oldest)
void	list_sort_time(t_node **head)
{
	t_node	*tmp;
	t_node	*prev;
	int		sorted;

	sorted = 0;
	while (!sorted)
	{
		tmp = *head;
		while (tmp && tmp->next)
		{
			if (tmp->sec < tmp->next->sec && tmp->n_sec < tmp->next->n_sec)
				update_list_time(prev, tmp, head, &sorted);
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
		if (sorted == 0)
			return ;
		sorted = 0;
	}
}

void	list_sort_time_dispatch(t_node **head, int opts)
{
	if (opts & REVERSE)
		list_sort_time_reverse(head);
	else
		list_sort_time(head);
}
