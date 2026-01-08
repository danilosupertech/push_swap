NAME        = push_swap
BONUS_NAME  = checker

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -Iincludes -Ilibft
RM          = rm -f
RM_DIR      = rm -rf

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# --- Source Files (with full paths) ---
PS_SRCS = \
    src/main.c \
    src/ops/swap_ops.c \
    src/ops/push_ops.c \
    src/ops/rotate_ops.c \
    src/ops/rev_rotate_ops.c \
    src/turk_algo.c \
    src/turk_calc_costs.c \
    src/turk_calc_setters.c \
    src/turk_calc_targets.c \
    src/turk_moves.c \
    src/turk_sort_utils.c \
    src/turk_finish.c \
    src/stack_utils.c \
    utils/stack_init.c \
    src/stack_ops.c \
    src/parsing.c

BONUS_SRCS = \
	bonus/checker/checker_main.c \
	src/ops/swap_ops.c \
	src/ops/push_ops.c \
	src/ops/rotate_ops.c \
	src/ops/rev_rotate_ops.c \
	src/stack_utils.c \
	utils/stack_init.c \
	src/stack_ops.c \
	src/parsing.c

# --- Objects ---
OBJ_DIR      = objs
PS_OBJS      = $(patsubst %.c,$(OBJ_DIR)/%.o,$(PS_SRCS))
BONUS_OBJS   = $(patsubst %.c,$(OBJ_DIR)/%.o,$(BONUS_SRCS))

# --- Rules ---
.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(PS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(PS_OBJS) $(LIBFT) -o $(NAME)
	@echo "push_swap compiled!"

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@echo "checker compiled!"

# Rule to compile .c files into .o files, creating subdirs in objs
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM_DIR) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all