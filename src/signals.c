/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:43:34 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/26 12:18:16 by jkromer          ###   ########.fr       */
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
	else
		ft_putchar('\n');
	*g_sig.status = 130;
}

static void	quit_handler(int s)
{
	(void)s;
	if (g_sig.pid != -1)
	{
		ft_puts("Quit");
		*g_sig.status = 131;
	}
}

void	init_signals(void)
{
	struct sigaction	quit_act;
	struct sigaction	int_act;

	quit_act.sa_handler = SIG_IGN;
	quit_act.sa_flags = 0;
	sigaction(SIGQUIT, &quit_act, NULL);
	int_act.sa_handler = int_handler;
	int_act.sa_flags = 0;
	sigaction(SIGINT, &int_act, NULL);
}

void	reset_quit_handler(void)
{
	struct sigaction	quit_act;

	quit_act.sa_handler = quit_handler;
	quit_act.sa_flags = 0;
	sigaction(SIGQUIT, &quit_act, NULL);
}

void	reset_int_handler(void)
{
	struct sigaction	int_act;

	int_act.sa_handler = SIG_DFL;
	int_act.sa_flags = 0;
	sigaction(SIGINT, &int_act, NULL);
}
