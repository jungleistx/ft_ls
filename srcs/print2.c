/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:40:33 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/20 15:47:41 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

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
	ft_printf("%s ", node->l_opt->permissions);
	ft_printf("%*d ", 3, node->l_opt->links);
	ft_printf("%-*s", 12, node->l_opt->owner);
	ft_printf("%-*s", 8, node->l_opt->group);
	ft_printf("%-*d ", 7, node->l_opt->size);
	ft_printf("%s ", node->l_opt->date);
	ft_printf("%s", node->name);
	if (node->type == 10)
		ft_printf(" -> %s", node->l_opt->sym_link);
	ft_printf("\n");
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
				ft_printf("%s\n", tmp->name);
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
