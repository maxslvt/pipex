/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masolet- <masolet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:49:17 by masolet-          #+#    #+#             */
/*   Updated: 2026/04/09 11:52:32 by masolet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (s_cmd[0] == NULL)
	{
		free(s_cmd);
		ft_error("split");
	}
	path = NULL;
	if (access(s_cmd[0], F_OK & X_OK) == 0)
		path = ft_strdup(s_cmd[0]);
	else
		path = get_path(s_cmd[0], env);
	if (!path)
	{
		ft_free_tab(s_cmd);
		ft_error("pipex: env not found\n");
	}
	if (execve(path, s_cmd, env) == -1)
	{
		ft_free_tab(s_cmd);
		free(path);
		ft_error("pipex: command not found\n");
	}
}

void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	close(p_fd[0]);
	fd = open_file(av[1], 0);
	dup2(fd, 0);
	close(fd);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	exec(av[2], env);
}

void	child2(char **av, int *p_fd, char **env)
{
	int		fd;

	close(p_fd[1]);
	fd = open_file(av[4], 1);
	dup2(fd, 1);
	close(fd);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		ft_error("Invalid number of arguments");
	if (pipe(p_fd) == -1)
		ft_error("pipe");
	pid1 = fork();
	if (pid1 == -1)
		ft_error("fork1");
	if (pid1 == 0)
		child(av, p_fd, env);
	pid2 = fork();
	if (pid2 == -1)
		ft_error("fork2");
	if (pid2 == 0)
		child2(av, p_fd, env);
	close(p_fd[1]);
	close(p_fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}