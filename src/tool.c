/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:03:44 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/03 09:04:13 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*v_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit (0);
	return (ret);
}

void	cleanup(char **paths, char *new_prog)
{
	free(new_prog);
	free_split(paths);
}
