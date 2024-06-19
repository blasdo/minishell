/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:09:44 by bvelasco          #+#    #+#             */
/*   Updated: 2024/06/19 17:01:47 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "minishell.h"
# include <sys/stat.h>

/*
 * NOC is the number of commands (command + arguments)
 * cmds are the commands itself (array)
 * env is the complete environment (check diagram for more information) 
 * info is the additional info:
 *  - 0 no additional info required
 *  - >0 additional info required, (there are an enum with the list of
 *  	general parse additional info)
 *  - <0 error in general parse, (there are an enum with the list of
 * 		general_parse errors)
 */
typedef struct s_input
{
	__uint8_t	noc;
	t_command	**cmds;
	t_list		**env;
	__int8_t	info;
}				t_input;

#endif