/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:04:00 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/26 15:08:08 by rvuorenl         ###   ########.fr       */
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
	// printf("%s %*d %s  %s %*d %s %s\n",node->l_opt->permissions, 3,
	// 	node->l_opt->links, node->l_opt->owner, node->l_opt->group, 8,
	// 	node->l_opt->size, node->l_opt->date, node->name);// 8?
	printf("%s   ", node->l_opt->permissions);
	printf("%d   ", node->l_opt->links);
	printf("%s   ", node->l_opt->owner);
	printf("%s   ", node->l_opt->group);
	printf("%d   ", node->l_opt->size);
	printf("%s   ", node->l_opt->date);
	printf("%s \n", node->name);
	// printf("%s %d %s %s %d %s %s\n", node->l_opt->permissions,
	// 	node->l_opt->links, node->l_opt->owner, node->l_opt->group,
	// 	node->l_opt->size, node->l_opt->date, node->name);
}

void	print_long_list(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s   ", tmp->l_opt->permissions);
		printf("%d   ", tmp->l_opt->links);
		printf("%s   ", tmp->l_opt->owner);
		printf("%s   ", tmp->l_opt->group);
		printf("%d   ", tmp->l_opt->size);
		printf("%s   ", tmp->l_opt->date);
		printf("%s \n", tmp->name);
		// printf("%s %d %s %s %d %s %s\n", tmp->l_opt->permissions,
		// 	tmp->l_opt->links, tmp->l_opt->owner, tmp->l_opt->group,
		// 	tmp->l_opt->size, tmp->l_opt->date, tmp->name);
		// printf("%s %*d %s  %s %*d %s %s\n",tmp->l_opt->permissions, 3,
		// 	tmp->l_opt->links, tmp->l_opt->owner, tmp->l_opt->group, 8,
		// 	tmp->l_opt->size, tmp->l_opt->date, tmp->name);// 8?
		tmp = tmp->next;
	}
}

void	print_list_files(t_node **head, int options)
{
	t_node	*tmp;

	tmp = *head;
	while(tmp)
	{
		if (tmp->type != 4 && tmp->type != 0)
		{
			if (options & LONG)
				print_long_list_node(tmp);
			else
				printf("%s\n", tmp->name);
 		}
		tmp = tmp->next;
	}
	// print_test(*head);
	free_file_nodes(head, options);
	// print_test(*head);
	// printf("sss\n");
	// print_test(*head);
	// printf("\n");
}

void	print_list_all(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s\t", tmp->name);
		tmp = tmp->next;
	}
	printf("\n");
}

void	print_list(t_node *head, int opts)
{
	if (opts & LONG)
		print_long_list(head);
	else
		print_list_all(head);
}

// void	print_dir_content(t_node *head, int opts)
void	print_dir(t_node *head, int opts)
{
	t_node	*tmp;
	t_node	*newhead;

	newhead = NULL;
	tmp = head;
	while (tmp)
	{
		printf("\n%s:\n", tmp->name);
		list_add_directory(&newhead, tmp->name, opts);
		// tmp->name works as a path, UNTESTED
		print_list(newhead, opts);
		tmp = tmp->next;
		free_list(&newhead, opts);
	}
}

void	print_dir_recursive(t_node **head, int opts)
{
	t_node	*tmp;
	t_node	*newhead;
	t_node	*rec_head;

	rec_head = NULL;
	newhead = NULL;
	tmp = *head;
	while (tmp)
	{
		printf("\n%s:\n", tmp->name);
		list_add_directory(&newhead, tmp->name, opts);
		rec_head = print_list_find_dir(newhead, opts);
		if (rec_head)
			print_dir_recursive(&rec_head, opts);
		tmp = tmp->next;
		free_list(&newhead, opts);
	}
	free_list(head, opts);
}

/*
recursion:

make list of node->name
print list
free filenodes (in print)
if folders -> recursion tmp->name
free list
*/
