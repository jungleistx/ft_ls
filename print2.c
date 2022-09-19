/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:40:33 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/19 18:04:49 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list_errors(t_node *head, t_info *info)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			if (info->options & FIRST_LINE)
				info->options ^= FIRST_LINE;
			info->options |= DIR_NAME;
			error_notfound(tmp->name);
			info->ret_nr = 1;
		}
		tmp = tmp->next;
	}
}

void	print_long_list_node(t_node *node)
{
	printf("%s ", node->l_opt->permissions);
	printf("%*d ", 3, node->l_opt->links);
	printf("%-*s", 12, node->l_opt->owner);
	printf("%-*s", 8, node->l_opt->group);
	printf("%-*d ", 7, node->l_opt->size);
	printf("%s ", node->l_opt->date);
	printf("%s", node->name);
	if (node->type == 10)
		printf(" -> %s", node->l_opt->sym_link);
	printf("\n");
}

void	print_list_files(t_node **head, t_info *info)
{
	t_node	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == 8 || tmp->type == 10)
		{
			if (info->options & FIRST_LINE)
				info->options ^= FIRST_LINE;
			info->options |= DIR_NAME;
			if (info->options & LONG)
				print_long_list_node(tmp);
			else
				printf("%s\n", tmp->name);
		}
		tmp = tmp->next;
	}
	free_file_nodes(head, info->options);
}

void	print_free_list(t_node **head, t_info *info)
{
	print_list(head, info);
	free_list(head, info->options);
}
