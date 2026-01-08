NAME        = push_swap
BONUS_NAME  = checker

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -Iincludes -Ilibft

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

OBJDIR      = objs

COMMON_SRCS = \
	utils/stack_init.c \
	utils/stack_split.c \
	utils/stack_split_utils.c \
	utils/parse_helpers.c \
	utils/stack_utils.c \
	utils/stack_ops.c

SRCS = \
	src/main.c \
	src/cmd_push.c \
	src/cmd_swap.c \
	src/cmd_rotate.c \
	src/cmd_rev_rotate.c \
	src/turk_algo.c \
	src/turk_calc_setters.c \
	src/turk_calc_targets.c \
	src/turk_calc_costs.c \
	src/turk_moves.c \
	src/turk_finish.c \
	src/turk_utils.c \
	src/turk_sort_utils.c \
	$(COMMON_SRCS)

BONUS_SRCS = \
	bonus/checker_main.c \
	bonus/checker_ops.c \
	bonus/checker_stack_ops.c \
	$(COMMON_SRCS)

OBJS        = $(SRCS:%.c=$(OBJDIR)/%.o)
BONUS_OBJS  = $(BONUS_SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
