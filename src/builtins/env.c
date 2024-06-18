/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:05:09 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/05 16:47:03 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_builtin(t_input *input, int i)
{
	char	**env;
	int		j;

	if (input->cmds[i]->argc != 1)
		return (1);
	j = 0;
	env = ft_getenv(input->env);
	while (env[j] != NULL)
	{
		printf("%s\n", env[j]);
		++j;
	}
	ft_free_ptr_array(env);
	return (0);
}
