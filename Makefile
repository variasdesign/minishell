NAME = minishell

CC				= clang
CFLAGS			= -Wextra -Wall -Werror
CFLAGS			+= -std=c99
CFLAGS			+= -ggdb3
# CFLAGS			+= -fsanitize=address
RM				= rm -rf

LIBFT_DIR		= ./libft
BUILD_DIR		= ./.build
BUILD_BASE_DIR	= $(BUILD_DIR)/base

HEADERS			= -I ./libft/include -I ./include
LIBFT_HEADERS	= $(LIBFT_DIR)/include/libft.h

LIBFT			= $(LIBFT_DIR)/libft.a
LIBS			= $(LIBFT)

BASE_DIR		= ./src
BASE_SRCS		= $(addprefix $(BASE_DIR)/,		\
					main.c						\
					)

BASE_OBJS		= $(BASE_SRCS:$(BASE_DIR)/%.c=$(BUILD_BASE_DIR)/%.o)

all: $(NAME)

$(NAME): $(BASE_OBJS) $(LIBFT)
	@echo "Generating minishell objects..."
	@$(CC) $(CFLAGS) $(BASE_OBJS) $(HEADERS) $(LIBS) -o $(NAME) -lreadline
	@echo "Done! :D"

$(BUILD_BASE_DIR)/%.o: $(BASE_DIR)/%.c $(BASE_HEADERS) $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@

$(LIBFT): $(LIBFT_HEADERS)
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "Done! :D"

clean:
	@echo "Cleaning objects..."
	@$(RM) $(BASE_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "Done! :D"

fclean: clean
	@echo "Cleaning all..."
	@$(RM) $(BUILD_DIR)
	@$(RM) $(NAME)
	@echo "Done! :D"

re: fclean all

.PHONY: all clean fclean re
