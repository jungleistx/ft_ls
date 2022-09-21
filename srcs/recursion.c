/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:20:35 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/21 21:47:22 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	check_null_head(t_node **head, t_inf *info)
{
	if (*head != NULL)
	{
		print_list(head, info);
		free_file_nodes(head, info->options);
	}
}

int	traverse_hidden_files(char *name)
{
	if (name[0] == '.')
	{
		if (name[1] == '\0' || (name[1] == '.' && name[2] == '\0'))
			return (0);
	}
	return (1);
}

void	print_dir_recursive(t_node **head, t_inf *info, int dot_dir)
{
	t_node	*tmp;
	t_node	*newhead;

	newhead = NULL;
	tmp = *head;
	while (tmp)
	{
		if (traverse_hidden_files(tmp->name) || dot_dir)
		{
			if (info->options & DIR_NAME)
				print_path(tmp->path, info);
			list_add_directory(&newhead, tmp->path, info, tmp->name);
			if (info->options & LON && newhead != NULL)
				ft_printf("total %ld\n", info->total);
			check_null_head(&newhead, info);
			if (newhead)
			{
				info->options |= DIR_NAME;
				print_dir_recursive(&newhead, info, 0);
			}
			free_list(&newhead, info->options);
		}
		tmp = tmp->next;
	}
	free_list(head, info->options);
}
