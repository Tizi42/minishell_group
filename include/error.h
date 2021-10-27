/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:22:39 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/21 16:47:40 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	print_error(const char *prog, const char *arg);
void	export_error(const char *arg);
void	exit_error(const char *arg);
void	execute_error(const char *arg);

#endif
