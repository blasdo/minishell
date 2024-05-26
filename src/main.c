/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:49:21 by bvelasco          #+#    #+#             */
/*   Updated: 2024/05/26 16:57:40 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//for debug pruporses
static void	print_input(t_input *input)
{
	int i;
	int	j;
	int	k;

	i = 0;
	printf("PROCESED INPUT:\n");
	printf("COMMANDS: %d\n", input->noc);
	while (i < input->noc)
	{
		j = 0;
		k = 0;
		printf("Command %i: \n", i);
		while (input->cmds[i]->args[j] != NULL)
			printf(" %s\n", input->cmds[i]->args[j++]);
		while (k < 3)
			printf(" %i", input->cmds[i]->fds[k++]);
		printf("\n");
		i++;
	}
}
static void	close_fds(t_command *cmd)
{
	if (cmd->fds[0] != 0)
		close(cmd->fds[0]);
	if (cmd->fds[1] != 1)
		close(cmd->fds[1]);
	if (cmd->fds[2] != 2)
		close(cmd->fds[2]);
}
static void	clear_input(t_input *input)
{
	int i;

	i = 0;
	while (i < input->noc)
	{
		close_fds(input->cmds[i]);
		ft_free_ptr_array(input->cmds[i]->args);
		free(input->cmds[i]);
	}
	free(input->cmds);

}

int main(int argc, char *argv[], char *envp[])
{
	t_list	*env;
	t_input	*input;
	char	*rawline;

	env = parse_env(envp);
	rawline = readline("mini$hell: ");
	while (rawline)
	{
		add_history(rawline);
		input = parse_line(env, rawline);
		print_input(input);
		//executer(input);
		ft_free_ptr_array(input->cmds[0]->args);
		free(input->cmds[0]);
		free(input->cmds);
		free(input);
		free(rawline);
		rawline = readline("mini$hell: ");
	}
	ft_lstclear_type(&env, clear_env_list);
	return (0);
}