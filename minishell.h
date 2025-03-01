/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:00:31 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/19 11:36:50 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include "libft/libft.h"
# include "ms_error.h"

# define PROMPT "minishell$ "
# define FILE_HIST ".minishell_history"

typedef struct s_vars
{
	char			*name;
	char			*value;
	struct s_vars	*next;
}					t_vars;

typedef struct s_shell
{
	int				exitst;
	int				lastst;
	char			*prompt;
	t_vars			*env;
	char			**envar;
	t_vars			*vars;
	int				isatty;
	struct termios	termios_backup;
}					t_shell;

typedef struct s_quo
{
	char			*qs;
	int				q;
	struct s_quo	*nxq;
}					t_quo;

typedef struct s_arg
{
	char			*ars;
	int				redir;
	t_quo			*aq;
	struct s_arg	*nxa;
}					t_arg;

typedef struct s_cmd
{
	char			*cmd;
	int				builtin;
	t_arg			*arl;
	char			**ara;
	int				fdout;
	int				fdin;
	int				pp[2];
	int				redirerror;
	struct s_cmd	*nxc;
}					t_cmd;

extern int	g_ctrlc;

extern int	errno;

// Main
int		init_shell(t_shell *ts, char **envp);
void	ms_run_cmds(char *cmd, t_shell *shdata, t_cmd *c);

// Sanitization
char	*ft_sanitize_cmd(char *cmd);
int		ft_sanitize_pipe(char *cmd, int i);
int		ft_sanitize_redir(char *cmd, int i);
char	*ft_sigcheck(char *cmd, int sig_quote);

// History management functions
int		ft_write_history(char *cmd, char *home);
int		ft_load_history(char *home);
int		ft_add_history(t_shell *sh, char *cmd);

// Input reading
int		*ms_sig_quote(char c, int *sig_quote);
char	*ms_read_line(t_shell *sh);

// Utils
int		ft_isredir(char c);
int		ft_isvarop(char c);
int		ft_isop(char c);
int		ft_isquote(char c);
int		ft_islogic(char c);
int		ft_isassign(char *s);
int		ft_ismeta(char c);
int		ft_isbuiltin(char *cmd);

// Parsing functions
char	*ft_sanitize_cmd(char *cmd);
t_cmd	*ms_expansion(t_shell *sh, t_cmd *cmd);
void	ms_clearargs(t_cmd *c);
void	ms_choose_cmd(t_cmd *c);
void	ms_quote_quo(t_quo *tq);
void	ms_quote(t_cmd *cmd);
int		ms_get_cmd(t_shell *sh, t_cmd *c);
char	*ms_strexp(t_shell *sh, char *s);
t_arg	*ms_argexp(t_shell *sh, t_arg *ar);
t_cmd	*ms_split_cmd(char *cl);
t_cmd	*ms_argsplit(t_cmd *c);
t_arg	*ms_redir_exp(t_shell *sh, t_arg *ar);
t_arg	*ms_redir_quo(t_arg *ar);

// Commands creation
t_cmd	*ms_new_cmd(char **s);
void	ms_cmdadd_back(t_cmd **lc, t_cmd *nc);

// Handle arguments lists
t_arg	*ft_argnew(void *content);
t_arg	*ft_argadd_back(t_arg *arg, t_arg *new);
t_arg	*ft_argadd_front(t_arg *arg, t_arg *new);
t_arg	*ft_insarg_after(t_arg *where, t_arg *what);
void	ft_delarg(t_arg **arg);
int		ms_get_args(t_cmd *c);

// Handle redirections
int		ms_redir(t_shell *sh, t_cmd *c);
int		ms_redirect(t_shell *sh, t_cmd *c, t_arg *a);
int		ms_aredirect(t_shell *sh, t_cmd *c, t_arg *a);
int		ms_inredirect(t_shell *sh, t_cmd *c, t_arg *a);
int		ms_heredoc(t_shell *sh, t_cmd *c, t_arg *a);

// Built-in functions
int		ms_echo(t_shell *sh, t_cmd *c);
int		ms_exit(t_shell *sh, t_cmd *c);
int		ms_env(t_shell *sh, t_cmd *c);
int		ms_export(t_shell *sh, t_cmd *c);
int		ms_unset(t_shell *sh, t_cmd *c);
int		ms_cd(t_shell *sh, t_cmd *c);
int		ms_pwd(t_shell *sh, t_cmd *c);
int		ms_run_builtin(t_shell *sh, t_cmd *c);

// Environmental and temporary variables
t_vars	*ms_new_var(char *nm, char *val);
t_vars	*ms_add_var(t_vars **vars, t_vars *var);
int		ms_set_env(t_shell *sh, char **envp);
char	**ms_get_env(t_shell *sh);
char	*ms_get_var(t_shell *sh, char *name);
int		ms_update_var(t_vars *var, char *value);
int		ms_free_var(t_vars **vl, t_vars *iv, t_vars *pv);
int		ms_check_varname(char *name);
char	*ms_exp_var(t_shell *sh, char **s);
int		ms_set_var(t_shell *sh, char *name, char *value);
int		ms_rm_var(t_shell *sh, char *name);

// running commands
int		ms_set_pipes(t_cmd *c);
int		ms_close_pipes(t_cmd *c);
int		ms_fork_cmds(t_shell *sh, t_cmd *c);

// free funtions
int		ms_free(t_shell *sh, t_cmd **c, char **sta);
void	*ms_free_strarr(char **sta);
t_cmd	*ms_free_cmds(t_cmd **c);

// quo functions
t_quo	*ms_new_quo(char *qs);
void	*ms_free_quo(t_quo *q);
void	*ms_free_quolst(t_quo *q);
t_quo	*ms_split_quo(t_arg *a);
t_arg	*ms_join_quo(t_arg *a);

// signal

int		set_sighandlers(void);
int		reset_sighandlers(void);
void	sigint_handler(int sig);

// auxiliar
int		ms_error(char *msg1, char *msg2, char *msg3, int head);
int		ms_errorf(char *f, char *s0, char *s1, char *s2);
char	*ms_straddchar(char *s, char c);
int		ft_atol_ms(char *s, long *lv);
char	*ms_strjoin3(char const *s1, char const *s2, char const *s3);

#endif
