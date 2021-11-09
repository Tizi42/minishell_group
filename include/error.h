/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:22:39 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/08 13:28:11 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* error.c */
void	print_error(const char *prog, const char *arg);
void	export_error(const char *arg);
void	exit_error(const char *arg);
void	execute_error(const char *arg);

/* error2.c */
int		open_error(const char *file);
void	syntax_error(const char *arg);

#endif
