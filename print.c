/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:04:00 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/19 18:04:55 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
}

void	print_dir(t_node *head, t_info *info)
{
	t_node	*tmp;
	t_node	*newhead;

	newhead = NULL;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			if (info->options & FIRST_LINE && info->options & DIR_NAME)
			{
				printf("%s:\n", tmp->name);
				info->options ^= FIRST_LINE;
			}
			else if (info->options & DIR_NAME)
				printf("\n%s:\n", tmp->name);
			list_add_directory(&newhead, tmp->name, info, tmp->name);
			if (info->options & LONG && newhead)
				printf("total %ld\n", info->total);
			print_free_list(&newhead, info);
		}
		else if (tmp->type == 1)
			print_sym_link(tmp, info->options);
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
