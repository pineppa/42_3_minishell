NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

RLLIB = -lreadline

SRCD = src/

SRCS = minishell.c history.c ms_signals.c \
		ms_vars.c ms_vars_tools.c ms_set_env.c \
		ms_builtin.c ms_builtin2.c ms_export.c \
		ms_redir_exp.c ft_atol_ms.c ms_quote.c \
		ms_checks.c ms_checks2.c ms_cmd.c \
		ft_sanitize_cmd.c ms_strexp.c \
		ms_lstarg.c ms_get_args.c ms_expand.c \
		ms_quo_tools.c ms_split_quo.c \
		ms_free.c ms_error.c ms_get_cmd.c ms_redir.c \
		ms_split_cmd.c ms_run_cmds.c \
		ms_pipes.c ms_heredoc.c ms_read_line.c
SRCSD = $(addprefix $(SRCD),$(SRCS))
HEADD = ./
HEADS = minishell.h ms_error.h

OBJS = $(SRCS:.c=.o)
OBJD = obj/
OBJSD = $(addprefix $(OBJD),$(OBJS))

DEPS = $(OBJSD:.o=.d)

LIBFTHD = libft/
LIBFT = $(LIBFTHD)libft.a

LIBFTCC = -I $(LIBFTHD) $(LIBFT)

all:
	@make --no-print-directory -C $(LIBFTHD) | sed '/Nothing to be done/d'
	@make --no-print-directory mandatory

mandatory: $(NAME)
	@echo "Minishell is available and up to date"

$(NAME): $(OBJSD) Makefile $(HEADS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(HEADD) -o $(NAME) $(OBJSD) $(LIBFTCC) $(RLLIB)

$(OBJD)%.o: $(SRCD)%.c Makefile $(HEADS)
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I $(HEADD) -MMD -o $@ -c $<

-include $(DEPS)

$(LIBFT):
	@make --no-print-directory -C $(LIBFTHD)

clean:
	$(RM) $(DEPS) $(OBJS)
	@make --no-print-directory -C $(LIBFTHD) clean

fclean: clean
	$(RM) $(NAME)
	@make --no-print-directory -C $(LIBFTHD) fclean

re: fclean all

ga:
	git add Makefile $(SRCSD) $(HEADS)
	@make --no-print-directory -C $(LIBFTHD) ga

gp:
	git push
	git push github

norm:
	norminette $(SRCSD) $(HEADS)
	@make --no-print-directory -C $(LIBFTHD) norm

.PHONY : norm mandatory re fclean clean all ga gp
