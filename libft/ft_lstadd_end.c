/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:11:59 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/23 14:30:44 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd_end(t_list *head, t_list *new)
{
	t_list	*copy;

	copy = head;
	while (copy->next != NULL)
		copy = copy->next;
	copy->next = new;
	new->next = NULL;
	return (head);
}
