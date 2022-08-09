/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:50:06 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/30 18:52:37 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*copy;

	if (!del)
		return ;
	copy = *alst;
	while (copy)
	{
		tmp = copy->next;
		del(copy->content, copy->content_size);
		free(copy);
		copy = tmp;
	}
	*alst = NULL;
}
