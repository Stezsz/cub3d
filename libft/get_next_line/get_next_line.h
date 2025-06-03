/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:56:36 by tborges-          #+#    #+#             */
/*   Updated: 2024/12/01 19:15:00 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

// main functions
char	*get_next_line(int fd);
char	*read_line(int fd, char *line);
char	*get_line(char *line);
char	*new_line(char *line);

// utils
size_t	ft_strlen_gnl(char *s);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *line, char *buff);

#endif
