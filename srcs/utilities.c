/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:03:32 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/21 20:24:06 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int	option_validity(char *str)
{
	int	i;
	int	dash;

	dash = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '-')
			dash++;
		if (str[i] != '-' && !(ft_strchr(OPTIONS, str[i])))
			return (0);
	}
	if (dash > 1)
		return (0);
	return (1);
}

void	shift_options(char *argv, t_inf *info)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (OPTIONS[++j])
		{
			if (OPTIONS[j] == argv[i])
				info->options |= (1 << j);
		}
	}
}

void	read_options(int argc, char **argv, t_inf *info)
{
	int	i;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
		{
			info->args = argc - i - 1;
			return ;
		}
		else if (!(option_validity(argv[i])))
			exit_illegal();
		else
			shift_options(&argv[i][1], info);
		i++;
	}
	if (i < argc)
		info->args = argc - i;
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

void	create_node_dots(t_node **head, char *name, t_inf *info)
{
	t_node		*node;
	struct stat	filestat;

	info->options |= DOT_ARG;
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		exit_malloc_error(name);
	node->path = ft_strdup_exit(name);
	if (lstat(node->path, &filestat) == -1)
	{
		node->type = 0;
		info->options |= ERROR_FILE;
	}
	else
		node->type = node_filetype(filestat, node, info->options);
	node->name = ft_strdup_exit(name);
	node->next = NULL;
	node->sec = filestat.st_mtimespec.tv_sec;
	node->n_sec = filestat.st_mtimespec.tv_nsec;
	if (info->options & LON && node->type != 0)
		list_add_long(node, filestat, info);
	list_sort_add(head, node, info->options);
}

void	read_arguments(t_node **head, int argc, char **argv, t_inf *info)
{
	if (info->args == 0)
	{
		list_add_directory(head, ".", info, "");
		if (info->options & LON)
			ft_printf("total %ld\n", info->total);
		print_current_dir(head, info);
		exit(0);
	}
	else
	{
		info->options |= SYM_LINK;
		if (info->args > 1)
			info->options |= DIR_NAME;
		while (info->args > 0)
		{
			if (argv[argc - info->args][0] == '.')
				create_node_dots(head, argv[argc - info->args], info);
			else if (argv[argc - info->args][0] == '/' ||
			argv[argc - info->args][0] == '~')
				create_node(head, argv[argc - info->args], info, "");
			else
				create_node(head, argv[argc - info->args], info, ".");
			info->args--;
		}
	}
}
