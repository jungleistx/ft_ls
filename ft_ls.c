/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:55:37 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/20 14:06:36 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strdup_exit(char *src)
{
	char	*ret;

	ret = ft_strdup((const char *)src);
	if (!ret)
		exit_dup_error("ft_strdup_exit");
	return (ret);
}

void	reset_info(t_info *info, t_node **head)
{
	info->options = 0;
	info->args = 0;
	*head = NULL;
	info->ret_nr = 0;
	info->options |= FIRST_LINE;
}



void	list_add_directory(t_node **head, char *path, t_info *i, char *name)
{
	DIR				*dir;
	struct dirent	*dp;

	i->total = 0;
	dir = opendir(path);
	if (!dir)
		error_dir(name);
	else
	{
		dp = readdir(dir);
		while (dp != NULL)
		{
			if (dp->d_name[0] != '.'
				|| (dp->d_name[0] == '.' && i->options & HIDDEN))
				create_node(head, dp->d_name, i, path);
			dp = readdir(dir);
		}
		closedir(dir);
	}
}

// void print_test(t_node *head)
// {
// 	t_node *tmp = head;
// 	while (tmp)
// 	{
// 		printf("(%s) -> (%s)\n", tmp->name, tmp->path);
// 		tmp = tmp->next;
// 	}
// 	printf("(NULL)\n");
// }

void print_test(t_node *head)
{
	t_node *tmp = head;
	while (tmp)
	{
		printf("(%s) -> ", tmp->name);
		tmp = tmp->next;
	}
	printf("(NULL)\n");
}

void	ft_ls(t_node **head, t_info *info)
{
	if (info->options & ERROR_FILE)
		print_list_errors(*head, info);
	print_list_files(head, info);
	if (info->options & RECURSIVE)
		print_dir_recursive(head, info);
	else
		print_dir(*head, info);
	if (head)
		free_list(head, info->options);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_node	*head;

	reset_info(&info, &head);
	if (argc > 1)
		read_options(argc, argv, &info);
	read_arguments(&head, argc, argv, &info);
	ft_ls(&head, &info);
	return (info.ret_nr);
}
