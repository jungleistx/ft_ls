/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:03:32 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/17 15:06:12 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reset_info(t_info *info, t_node *head)
{
	info->options = 0;
	info->args = 0;
	info->path = NULL; 		// needed ?
	head = NULL;
}

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
	}
	if (dash > 1)
		return (0);		//	too many '-', exit_illegal
	return (1);			//	valid option
}

void	shift_options(char *argv, t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (OPTIONS[++j])	//	traverse the valid options
		{
			if (OPTIONS[j] == argv[i])	//	compare with the char in argv
			{
				if (info->options ^ (1 << j))	//	if not on already
					info->options |= (1 << j);	//	turn the correct option on
			}
		}
	}
}

void	read_options(int argc, char **argv, t_info *info)
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
			shift_options(&argv[i][1], info);	//	start from the next to '-'
		i++;
	}
	if (i < argc)
		info->args = argc - i;
}
