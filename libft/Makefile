NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar
ARFLAGS = rcs

MAKE = make

SRCS = ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c \
        ft_bzero.c ft_itoa.c ft_putendl_fd.c ft_strjoin.c ft_strrchr.c \
        ft_calloc.c ft_memchr.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c \
        ft_isalnum.c ft_memcmp.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c \
        ft_isalpha.c ft_memcpy.c ft_split.c ft_strlen.c ft_tolower.c \
        ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c \
        ft_isdigit.c ft_memset.c ft_strdup.c ft_strncmp.c \
		ft_strcmp.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
        ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
        ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		ft_uitoa.c ft_uitoa_base.c \
		ft_printf.c ft_flags.c ft_prfchar.c ft_prfstr.c \
		ft_prfnbr.c ft_prfhexa.c \
		ft_free.c get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

HEADD = ./
HEADS = libft.h

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -I $(HEADD) -MMD -o $(<:.c=.o) -c $<

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all

ga:
	git add $(SRCS) Makefile $(HEADS)

gp:
	git push
	git push github

norm:
	norminette $(SRCS) $(HEADS)

.PHONNY : bonus re fclean clean all
