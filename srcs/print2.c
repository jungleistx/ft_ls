/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:40:33 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/23 17:40:19 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	print_list_errors(t_node *head, t_inf *info)
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
	ft_printf("%-*s ", 12, node->l_opt->owner);
	ft_printf("%-*s ", 8, node->l_opt->group);
	print_major_minor(node);
	print_year(node);
	ft_printf("%s", node->name);
	if (node->type == 10)
		ft_printf(" -> %s", node->l_opt->sym_link);
	ft_printf("\n");
}

void	print_list_files(t_node **head, t_inf *info)
{
	t_node	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type != 4 && tmp->type != 0)
		{
			if (info->options & FIRST_LINE)
				info->options ^= FIRST_LINE;
			info->options |= DIR_NAME;
			if (info->options & LON)
				print_long_list_node(tmp);
			else
				ft_printf("%s\n", tmp->name);
		}
		tmp = tmp->next;
	}
	free_file_nodes(head, info->options);
}

void	print_free_list(t_node **head, t_inf *info)
{
	print_list_errors(*head, info);
	free_error_nodes(head, info->options);
	print_list(head, info);
	free_list(head, info->options);
}

void	print_current_dir(t_node **head, t_inf *info)
{
	print_list(head, info);
	if (info->options & RECURSIVE)
	{
		info->options |= PRINT_PATH;
		free_non_dir_nodes(head, info->options);
		print_dir_recursive(head, info, 0);
	}
	else
		free_list(head, info->options);
}
