/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:04:00 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/18 13:47:20 by rvuorenl         ###   ########.fr       */
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
	// if (node->type == 10 || node->type == 1)			// ???
	if (node->type == 10)
		printf(" -> %s", node->l_opt->sym_link);
	printf("\n");
}

void	print_long_list(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s ", tmp->l_opt->permissions);
		printf("%*d ", 3, tmp->l_opt->links);
		printf("%-*s", 12, tmp->l_opt->owner);
		printf("%-*s", 8, tmp->l_opt->group);
		printf("%*d ", 7, tmp->l_opt->size);
		printf("%s ", tmp->l_opt->date);
		printf("%s", tmp->name);
		if (tmp->type == 10)
			printf(" -> %s", tmp->l_opt->sym_link);
		printf("\n");
		tmp = tmp->next;
	}
}

void	print_list_files(t_node **head, t_info *info)
{
	t_node	*tmp;
	int		newline;

	newline = 0;
	tmp = *head;
	// print_test(*head);
	while(tmp)
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
	// print_test(*head);
	free_file_nodes(head, info->options);
}

void	print_list_all(t_node *head, t_info *info)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == 1 && info->options & SYM_LINK)
			print_sym_link(tmp, info->options);
		else
			printf("%s\n", tmp->name);
		tmp = tmp->next;
		info->options |= DIR_NAME;
	}
}

void	print_list(t_node **head, t_info *info)
{
	if (info->options & LONG)
		print_long_list(*head);
	else
		print_list_all(*head, info);
	printf("\n");
}

void	print_dir(t_node *head, t_info *info)
{
	t_node	*tmp;
	t_node	*newhead;

	// print_test(head);
	newhead = NULL;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			if (info->options & DIR_NAME)
				printf("%s:\n", tmp->name);
			list_add_directory(&newhead, tmp->name, info, tmp->name);
			if (info->options & LONG)
				printf("total %ld\n", info->total);
			print_list(&newhead, info);
			free_list(&newhead, info->options);
		}
		else if (tmp->type == 1)
		{
			print_sym_link(tmp, info->options);
		}
		tmp = tmp->next;
	}
}

void	print_path(char *str, int opts)
{
	if (str[0] == '/' && str[1] == '/')
		printf("%s:\n", &str[1]);
	else if (str[0] == '/')
		printf("%s:\n", str);
	else if (opts & RECURSIVE)
		printf("%s:\n", str);
	else
		printf("%s:\n", &str[2]);
}


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
			// if (newhead != NULL)
			// {
			// 	print_list(&newhead, info);
			// 	free_file_nodes(&newhead, info->options);
			// }
			// else
			// 	printf("\n");
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

/*
recursion:

make list of node->name
print list
free filenodes (in print)
if folders -> recursion tmp->name
free list
*/
