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
    src/commands/swap_ops.c \
    src/commands/push_ops.c \
    src/commands/rotate_ops.c \
    src/commands/rev_rotate_ops.c \
    src/algorithm/turk_sort.c \
    src/algorithm/small_cases.c \
    src/algorithm/final_rotation.c \
    src/algorithm/init_nodes.c \
    src/algorithm/find_targets.c \
    src/algorithm/calc_costs.c \
    src/algorithm/execute_moves.c \
    src/algorithm/rotation_moves.c \
	src/stack/stack_nav.c \
	src/stack/stack_order.c \
	src/stack/stack_ops.c \
    src/parsing/input_to_stack.c \
    src/parsing/parse_split.c \
    src/parsing/parse_split_free.c \
    src/parsing/parse_validate.c

BONUS_SRCS = \
	bonus/checker/checker_main.c \
	bonus/checker/checker_ops.c \
	src/commands/swap_ops.c \
	src/commands/push_ops.c \
	src/commands/rotate_ops.c \
	src/commands/rev_rotate_ops.c \
	src/stack/stack_nav.c \
	src/stack/stack_order.c \
	src/stack/stack_ops.c \
	src/parsing/input_to_stack.c \
	src/parsing/parse_split.c \
	src/parsing/parse_split_free.c \
	src/parsing/parse_validate.c

# --- Objects ---
OBJ_DIR      = objs
PS_OBJS      = $(patsubst %.c,$(OBJ_DIR)/%.o,$(PS_SRCS))
BONUS_OBJS   = $(patsubst %.c,$(OBJ_DIR)/%.o,$(BONUS_SRCS))

# --- Rules ---
.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: all $(BONUS_NAME)

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