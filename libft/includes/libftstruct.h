/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftstruct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:08:59 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 21:04:40 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSTRUCT_H
# define LIBFTSTRUCT_H
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4095
# endif

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_buffer
{
	int				size;
	char			content[BUFFER_SIZE + 1];
}					t_buffer;

typedef struct		s_print
{
	int				align;
	int				zero;
	int				field;
	int				precision;
	int				type;
	int				fd;
}					t_print;

typedef int	(*t_func)(t_print, va_list);

#endif
