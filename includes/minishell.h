/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:01:24 by bvelasco          #+#    #+#             */
/*   Updated: 2024/05/29 19:06:05 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// system 
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include <stdlib.h>
// external libraries
# include <readline/history.h>
# include <readline/readline.h>
# include <libft.h>
// project include files
# include "environment.h"
# include "command.h"
# include "input.h"
# include "parser.h"
# include "cleaners.h"
# include <sys/wait.h>

//FDS
enum
{
	FDIN = 0,
	FDOUT = 1,
	FDERROR = 2
};
//GENERAL ERRORS
typedef enum e_error
{
	VIEW = 1,
	NOT_IDENTIFIED = 2,
	ERRMEM = 3,
	ERRNFOUND = 4,
	ERRFORMAT = 5,
	ERROEMPTY = 6
}			t_error;
// end of error functions
void	exec_one(t_input *input);
void	exec_multiple(t_input *input);
char	*ft_joinpaths(char *p1, char *p2);
char	*get_command_location(char *cmd, t_list *env);

char	*get_cmd(char *cmd, t_list *env);
void	redirs(t_input *input, int i, int **pipes);

void	init_pipes(t_input *input, int ***pipes);
void	close_pipes(int **pipes, int noc);
void	free_pipes(int **pipes, int noc);
#endif
