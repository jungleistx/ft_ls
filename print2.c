/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:40:33 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/18 15:43:16 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list_errors(t_node *head, t_info *info)
{
	t_node	*tmp;
	int		newline;

	newline = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			newline = 1;
			info->options |= DIR_NAME;
			error_notfound(tmp->name);
			info->ret_nr = 1;
		}
		tmp = tmp->next;
	}
	if (newline)
		printf("\n");
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
	int		newline;

	newline = 0;
	tmp = *head;
	while (tmp)
	{
		if (tmp->type != 4 && tmp->type != 0 && tmp->type != 1)
		{
			newline = 1;
			info->options |= DIR_NAME;
			if (info->options & LONG)
				print_long_list_node(tmp);
			else
				printf("%s\n", tmp->name);
		}
		tmp = tmp->next;
	}
	if (newline)
		printf("\n");
	free_file_nodes(head, info->options);
}
