/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:20:35 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/19 15:21:40 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_null_head(t_node **head, t_info *info)
{
	if (*head != NULL)
	{
		print_list(head, info);
		free_file_nodes(head, info->options);
	}
	else
		printf("\n");
}

void	print_dir_recursive(t_node **head, t_info *info)
{
	t_node	*tmp;
	t_node	*newhead;

	newhead = NULL;
	tmp = *head;
	while (tmp)
	{
		if (tmp->name[0] != '.')
		{
			if (info->options & DIR_NAME)
				print_path(tmp->path, info->options);
			list_add_directory(&newhead, tmp->path, info, tmp->name);
			if (info->options & LONG && newhead != NULL)
				printf("total %ld\n", info->total);
			check_null_head(&newhead, info);
			if (newhead)
			{
				info->options |= DIR_NAME;
				print_dir_recursive(&newhead, info);
			}
			free_list(&newhead, info->options);
		}
		tmp = tmp->next;
	}
	free_list(head, info->options);
}
