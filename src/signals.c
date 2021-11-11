/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:43:34 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/10 18:53:52 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	term_handler_main(int s)
{
	(void)s;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// update exec.status
}

void	quit_handler_child(int s)
{
	(void)s;
	ft_puts("Quit");
	kill(0, SIGQUIT);
}

static void	term_handler_child(int s)
{
	(void)s;
	kill(0, SIGTERM);
}

void init_signals_main(void)
{
	struct sigaction	quit_act;
	struct sigaction	int_act;

	quit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &quit_act, NULL);
	int_act.sa_handler = term_handler_main;
	sigaction(SIGINT, &int_act, NULL);
}

void init_signals_child(void)
{
	struct sigaction	quit_act;
	struct sigaction	int_act;

	quit_act.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &quit_act, NULL);
	int_act.sa_handler = term_handler_child;
	sigaction(SIGINT, &int_act, NULL);
}
