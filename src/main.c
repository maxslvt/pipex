/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masolet- <masolet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:49:17 by masolet-          #+#    #+#             */
/*   Updated: 2026/04/09 14:46:11 by masolet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;
	int		errno_code;

	s_cmd = ft_split(cmd, ' ');
	if (s_cmd == NULL || s_cmd[0] == NULL)
	{
		free(s_cmd);
		ft_printerror(ERR_SPLIT, 1);
	}
	path = NULL;
	if (access(s_cmd[0], X_OK) == 0)
		path = ft_strdup(s_cmd[0]);
	else
		path = get_path(s_cmd[0], env);
	if (!path)
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		errno_code = 127;
		if (errno == EACCES)
			errno_code = 126;
		if (errno_code == 126)
			perror(cmd);
		else
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		ft_free_tab(s_cmd);
		free(path);
		exit(errno_code);
	}
}

void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	close(p_fd[0]);
	fd = open_file(av[1], 0);
	if (dup2(fd, 0) == -1)
		ft_printerror("dup2", 1);
	close(fd);
	if (dup2(p_fd[1], 1) == -1)
		ft_printerror("dup2", 1);
	close(p_fd[1]);
	exec(av[2], env);
}

void	child2(char **av, int *p_fd, char **env)
{
	int		fd;

	close(p_fd[1]);
	fd = open_file(av[4], 1);
	if (dup2(fd, 1) == -1)
		ft_printerror("dup2", 1);
	close(fd);
	if (dup2(p_fd[0], 0) == -1)
		ft_printerror("dup2", 1);
	close(p_fd[0]);
	exec(av[3], env);
}

static int	wait_last_status(pid_t pid1, pid_t pid2)
{
	int	status;

	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		ft_printerror(ERR_USAGE, 1);
	if (pipe(p_fd) == -1)
		ft_printerror(ERR_PIPE, 1);
	pid1 = fork();
	if (pid1 == -1)
		ft_printerror(ERR_FORK1, 1);
	if (pid1 == 0)
		child(av, p_fd, env);
	pid2 = fork();
	if (pid2 == -1)
		ft_printerror(ERR_FORK2, 1);
	if (pid2 == 0)
		child2(av, p_fd, env);
	close(p_fd[1]);
	close(p_fd[0]);
	return (wait_last_status(pid1, pid2));
}
