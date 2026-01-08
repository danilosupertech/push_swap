NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJDIR = ../objs/libft

SRCS = ft_strlen.c ft_strdup.c ft_atol.c ft_calloc.c ft_bzero.c ft_isdigit.c \
	ft_strncmp.c ft_putstr_fd.c ft_substr.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
