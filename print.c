/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:04:00 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/07 13:37:02 by rvuorenl         ###   ########.fr       */
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
		printf("%s\n", tmp->name);
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

// void	list_add_dir_path(t_node **head, char *path, int opts, char *full)
// {
// 	DIR				*dir;
// 	struct dirent	*dp;

// 	dir = opendir(path);
// 	if (!dir)
// 		error_dir("list_add_directory");		//	proper error code ???
// 	dp = readdir(dir);
// 	while (dp != NULL)
// 	{
// 		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && (opts & HIDDEN)))
// 			create_node_fullpath(head, dp->d_name, opts, );
// 		dp = readdir(dir);
// 	}
// 	closedir(dir);
// 	if (opts & SORT_TIME && opts & REVERSE)
// 		list_sort_time_reverse(head);
// 	else if (opts & SORT_TIME)
// 		list_sort_time(head);
// }

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
		if (tmp->name[0] != '.')
		{
			tmp->name = get_full_path(tmp->name, tmp->path);
			// free(tmp->path);
			printf("\n%s:\n", tmp->name);
			list_add_directory(&newhead, tmp->name, opts);

			// recursive -> save the name of first dir as a "path"
			// tmp->name / dir_name ...

			rec_head = print_list_find_dir(newhead, opts);
			if (rec_head)
				print_dir_recursive(&rec_head, opts);
			free_list(&newhead, opts);
		}
		tmp = tmp->next;
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
