/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 22:04:31 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/25 22:04:33 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/types.h>
# include "../libft/libft.h"

# define ENDL '\n'
# define BUFF_SIZE 30

int get_next_line(const int fd, char **line);
int	read_tmp(const int fd, char **buf);

#endif
