/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:04:00 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/25 14:00:46 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list_errors(t_node *head, int *ret_nr)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			error_notfound(tmp->name);
			*ret_nr = 1;
		}
		tmp = tmp->next;
	}
}

void	print_long_list_node(t_node *node)
{
	printf("%s %*d %s  %s %*d %s %s\n",node->l_opt->permissions, 3,
		node->l_opt->links, node->l_opt->owner, node->l_opt->group, 8,
		node->l_opt->size, node->l_opt->date, node->name);// 8?
}

void	print_long_list(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s %*d %s  %s %*d %s %s\n",tmp->l_opt->permissions, 3,
			tmp->l_opt->links, tmp->l_opt->owner, tmp->l_opt->group, 8,
			tmp->l_opt->size, tmp->l_opt->date, tmp->name);// 8?
		tmp = tmp->next;
	}
}

void	print_list_files(t_node *head, int options)
{
	t_node	*tmp;

	tmp = head;
	while(tmp)
	{
		if (tmp->type != 4 && tmp->type != 0)
		{
			if (options & LONG)
				print_long_list(tmp);
			else
				printf("%s\n", tmp->name);
 		}
		tmp = tmp->next;
	}
	print_test(head);
	free_file_nodes(head, options);
}

void	print_list_all(t_node *head, int opts)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	free_file_nodes(head, opts);
}

void	print_list(t_node *head, int opts)
{
	if (opts & LONG)
		print_long_list(head);
	else
		print_list_all(head, opts);
}

void	print_dir(t_node *head, int opts)
{
	t_node	*tmp;
	t_node	*newhead;

	tmp = head;
	while (tmp)
	{
		printf("%s:\n", tmp->name);
		list_add_directory(&newhead, tmp->name, opts);
		print_list(newhead, opts);
		tmp = tmp->next;
		free_list(&newhead, opts);
	}
	// free_list(head, opts);
}

void	print_dir_recursive(t_node *head, int opts)
{
	t_node	*tmp;
	t_node	*newhead;

	tmp = head;
	while (tmp)
	{
		printf("%s:\n", tmp->name);
		list_add_directory(&newhead, tmp->name, opts);
		print_list(newhead, opts);
		tmp = tmp->next;
	}
}

/*

recursion:

make list of node->name
print list
free filenodes (in print)
if folders -> recursion tmp->name
free list

*/
