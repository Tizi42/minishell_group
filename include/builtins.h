/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:13:04 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/27 12:05:14 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"

unsigned char	cd(const char *path);
unsigned char	pwd(void);
unsigned char	echo(char *const *args);
unsigned char	exit_builtin(char *const *args,	unsigned char last);
unsigned char	export(char *const *args, t_list **env);
unsigned char	unset(char *const *args, t_list **env);
unsigned char	env_builtin(const t_list *env);

#endif
