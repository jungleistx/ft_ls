/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:04:00 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/13 11:55:16 by rvuorenl         ###   ########.fr       */
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

	tmp = *head;
	while(tmp)
	{
		if (tmp->type != 4 && tmp->type != 0)
		{
			info->options |= DIR_NAME;
			if (info->options & LONG)
				print_long_list_node(tmp);
			else
				printf("%s\n", tmp->name);
 		}
		tmp = tmp->next;
	}
	// print_test(*head);
	free_file_nodes(head, info->options);
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
	// printf("\n");
}

void	print_list(t_node **head, int opts)
{
	if (opts & LONG)
		print_long_list(*head);
	else
		print_list_all(*head);
	// free_file_nodes(head, opts);
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

// void	print_dir(t_node *head, int opts)
void	print_dir(t_node *head, t_info *info)
{
	t_node	*tmp;
	t_node	*newhead;

	newhead = NULL;
	tmp = head;
	while (tmp)
	{
		if (info->options & DIR_NAME || find_multiple_dirs(newhead))
			printf("%s:\n", tmp->name);

		list_add_directory(&newhead, tmp->name, info);

		if (info->options & LONG)
			printf("total = %ld\n", info->total);

		// tmp->name works as a path, UNTESTED

		print_list(&newhead, info->options);
		tmp = tmp->next;
		// free_list(&newhead, opts);
	}
}

int	find_multiple_dirs(t_node *head)
{
	t_node	*tmp;
	int		dirs;

	dirs = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == 4)
			dirs++;
		tmp = tmp->next;
	}
	if (dirs > 1)
		return (1);
	return (0);
}

// void	print_dir_recursive(t_node **head, int opts)
void	print_dir_recursive(t_node **head, t_info *info)
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
			// printf("\n%s:\n", tmp->name);
			list_add_directory(&newhead, tmp->name, info);

			if (info->options & DIR_NAME || find_multiple_dirs(newhead))
				printf("%s:\n", tmp->name);
			if (info->options & LONG)
				printf("total = %ld\n", info->total);

			// recursive -> save the name of first dir as a "path"
			// tmp->name / dir_name ...

			print_list(&newhead, info->options);
			free_file_nodes(&newhead, info->options);
			if (newhead)
			{
				info->options |= DIR_NAME;
				print_dir_recursive(&newhead, info);
			}

			// rec_head = print_list_find_dir(newhead, opts);
			// if (rec_head)
			// 	print_dir_recursive(&rec_head, opts);
			// free_list(&newhead, opts);
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
