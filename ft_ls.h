/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:01:47 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/09 14:44:10 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h> // perror
# include <string.h> // strerror
# include <time.h> // ctime time
# include <dirent.h> // open- read- closedir, works with sys/types?
# include <sys/stat.h> // lstat
# include <pwd.h> // getpwuid
# include <sys/types.h> //getgrgid getpwuid
# include <grp.h> // getgrgid
# include <unistd.h> // readlink
# include "./libft/libft.h"
# include <stdlib.h>		// --------------------	 DELETE ??	----------------

# define OPTIONS lRart //ufgdG, bonus P

typedef	struct	s_node
{
	char			*name;
	struct s_node	*prev;
	struct s_node	*next;
	int				type;	// 4 directory, 8 file, 0 other.
}				t_node;

typedef	struct	s_info
{
	uint16_t	options;
	char		*path;

}				t_info;

typedef	struct	s_dirlist
{
	char			*name;
	struct s_node	*prev;
	struct s_node	*next;
	int				type;	// 4 directory, 8 file, 0 other.
}				t_dirlist;

typedef	struct s_arguments
{
	struct s_arguments	*next;
	char				*name;
}				t_arguments;

// 	lRart
typedef	enum e_options
{
	LONG = 1,
	RECURSIVE = 2,
	HIDDEN = 4,
	REVERSE = 8,
	SORT_TIME = 16
	/*
	BONUS OPTIONS
	*/
}t_options;

// void	arguments(int argc, char **argv, t_info *info);
void	exit_usage(void);
void	read_options(char *options, t_info *info);
void	reset_info(t_info *info);
void	ft_ls(int argc, char **argv, t_info *info);

#endif

/*	exit codes

1	exit_usage

*/


/*	bitwise operators

& (AND)	takes two numbers, is 1 if both are 1
	1100
&	0101
=	0100

| (OR) takes two numbers, is 1 if any is 1
	1100
|	0101
=	1101

^ (XOR) takes two numbers, XOR, 1 if two bits are different
	1100
^	0101
=	1001

<< (left shift) takes two numbers, 1st to shift, 2nd how much
	0011
<< 2
=	1100

>> (right shift) takes two numbers, 1st to shift, 2nd how much
	1100
>> 2
=	0011

~ (NOT) takes one number and inverts
~	1101
= 	0010

a = 	00000101
b = 	00001001
~a = 	11111010

b<<1 =	00010010
b>>1 = 	00000100
a ^ b = 00001100
a & b = 00000001
a | b =	00001101

shift
63	0000 0000 0000 0000 48
47	0000 0000 0000 0000 32
31	0000 0000 0000 0000 16
15	0000 0000 0000 0000 0

*/
