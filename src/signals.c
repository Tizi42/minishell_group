/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:43:34 by jkromer           #+#    #+#             */
/*   Updated: 2021/12/02 19:10:23 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_sig	g_sig;

static void	int_handler(int s)
{
	(void)s;
	if (g_sig.pid == -1)
	{
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	*g_sig.status = 130;
}

static void	quit_handler(int s)
{
	(void)s;
	if (g_sig.pid != -1)
		*g_sig.status = 131;
}

void	init_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, int_handler);
}

void	reset_quit_handler(void)
{
	signal(SIGQUIT, quit_handler);
}

void	reset_int_handler(void)
{
	signal(SIGINT, SIG_DFL);
}
