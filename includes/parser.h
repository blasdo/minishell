/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:53:25 by bvelasco          #+#    #+#             */
/*   Updated: 2024/04/23 18:29:50 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

t_list	*parse_env(char **envp);
/*
* Parse_line is the "main" function of line parser.
* There are more information in input.h
* RETURN:
* t_input * that contain all comands and information for process then
*/
t_input	*parse_line(char *input, t_list *env);

#endif