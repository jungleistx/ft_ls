/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:20:35 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/13 15:25:49 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node	*print_list_find_dir(t_node *head, int opts)
{
	t_node	*tmp;
	t_node	*dir;

	tmp = head;
	dir = NULL;
	while (tmp)
	{
		if (opts & LONG)
			print_long_list_node(tmp);
		else
			printf("%s\n", tmp->name);
		if (tmp->type == 4 && !dir)		//  find the first dir
			dir = tmp;
		tmp = tmp->next;
	}
	return (dir);
}
