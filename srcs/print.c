/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:04:00 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/23 20:15:41 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	print_long_list(t_node *head, t_inf *info)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type != 0)
		{
			ft_printf("%s ", tmp->l_opt->permissions);
			ft_printf("%*d ", 3, tmp->l_opt->links);
			ft_printf("%-*s ", 12, tmp->l_opt->owner);
			ft_printf("%-*s ", 8, tmp->l_opt->group);
			print_major_minor(tmp);
			print_year(tmp);
			ft_printf("%s", tmp->name);
			if (tmp->type == 10)
				ft_printf(" -> %s", tmp->l_opt->sym_link);
			ft_printf("\n");
		}
		else
			error_notfound(tmp->name);
		tmp = tmp->next;
		if (info->options & FIRST_LINE)
			info->options ^= FIRST_LINE;
	}
}

void	print_list_all(t_node *head, t_inf *info)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == 1 && info->options & SYM_LINK)
			print_sym_link(tmp, info->options);
		else
			ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
		info->options |= DIR_NAME;
		if (info->options & FIRST_LINE)
			info->options ^= FIRST_LINE;
	}
}

void	print_list(t_node **head, t_inf *info)
{
	if (info->options & LON)
		print_long_list(*head, info);
	else
		print_list_all(*head, info);
	if (!(info->options & FIRST_LINE))
		info->options |= DIR_NAME;
}

void	print_dir(t_node *head, t_inf *info)
{
	t_node	*tmp;
	t_node	*newhead;

	newhead = NULL;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			info->options |= PRINT_PATH;
			if (info->options & DIR_NAME)
				print_path(tmp->name, info);
			list_add_directory(&newhead, tmp->name, info, tmp->name);
			if (info->options & LON && newhead)
				ft_printf("total %ld\n", info->total);
			print_free_list(&newhead, info);
		}
		else if (tmp->type == 1)
			print_sym_link(tmp, info->options);
		tmp = tmp->next;
	}
}

void	print_path(char *str, t_inf *info)
{
	if (!(info->options & FIRST_LINE))
		ft_printf("\n");
	if (str[0] == '/' && str[1] == '/')
		ft_printf("%s:\n", &str[1]);
	else if (str[0] == '/')
		ft_printf("%s:\n", str);
	else if (info->options & PRINT_PATH || info->options & DOT_ARG)
		ft_printf("%s:\n", str);
	else
		ft_printf("%s:\n", &str[2]);
	if (info->options & FIRST_LINE)
		info->options ^= FIRST_LINE;
}
