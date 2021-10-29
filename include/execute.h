/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:00:08 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/27 19:02:08 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

t_list	*init_env(char **envp);
int		execute(char *const *args, t_list *env, int last_status);
char	*search_path(const char *prog);

#endif
