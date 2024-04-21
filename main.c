/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:29:48 by bvelasco          #+#    #+#             */
/*   Updated: 2024/04/21 18:30:09 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_input *input;
	t_list	*env;
	char	*line;
	char 	**envc;

	env = parse_env(envp);
	ft_putendl_fd(get_env_var(env, argv[1]), 1);
	set_env_var(&env, argv[1], ft_strdup(argv[2]));
	envc = ft_getenv(env);
	for (int i = 0; envc[i]; i++)
		printf("%s", envc[i]);
	return (0);
}
