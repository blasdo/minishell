/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:43:32 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/23 18:34:21 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signum = 0;

static void	sigint_handler_tty(int signum)
{
	g_signum = signum;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit_handler_tty(int signum)
{
	g_signum = signum;
	rl_on_new_line();
	rl_redisplay();
}

static void	sig_handler_tty(int status)
{
	g_signum = status;
	if (status == SIGINT)
		sigint_handler_tty(status);
	else if (status == SIGQUIT)
		sigquit_handler_tty(status);
}

void	signals_tty(void)
{
	signal(SIGINT, sig_handler_tty);
	signal(SIGQUIT, sig_handler_tty);
}
