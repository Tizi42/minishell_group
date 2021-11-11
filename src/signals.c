/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:43:34 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/11 11:27:28 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	term_handler(int s)
{
	(void)s;
	if (g_sig.pid == 0)
	{
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		*g_sig.status = 130;
	}
	else
		ft_putchar('\n');
}

static void	quit_handler(int s)
{
	(void)s;
	if (g_sig.pid != 0)
		ft_puts("Quit");
}

void init_signals(void)
{
	struct sigaction	quit_act;
	struct sigaction	int_act;

	quit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &quit_act, NULL);
	int_act.sa_handler = term_handler;
	sigaction(SIGINT, &int_act, NULL);
}

void	reset_quit_handler(void)
{
	struct sigaction	quit_act;

	quit_act.sa_handler = quit_handler;
	sigaction(SIGQUIT, &quit_act, NULL);
}
