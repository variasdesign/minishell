NAME = minishell

CC				= clang
CFLAGS			= -Wextra -Wall -Werror
CFLAGS			+= -std=c99
CFLAGS			+= -ggdb3
#CFLAGS			+= -fsanitize=address
INCLUDES		= -I ./libft/include -I ./include
RM				= rm -rf

LIBFT_DIR		= ./libft
BUILD_DIR		= ./.build
BUILD_BASE_DIR	= $(BUILD_DIR)/base

LIBFT			= $(LIBFT_DIR)/libft.a
READLINE		= -lreadline -lhistory
LIBS			= $(LIBFT) $(READLINE)

SRC_DIR			= src
SRC_DIR_EX		= src/expander
SRC_DIR_EXE		= src/exec
SRC_DIR_LEX		= src/lexer
SRC_DIR_SIG		= src/signal
SRC_DIR_PAR		= src/parser
SRC_DIR_UT		= src/utils
SRC_DIR_BU		= src/builtins

BASE_SRCS		= $(addprefix $(SRC_DIR)/,		\
					main.c						\
					)

BASE_SRCS		+= $(addprefix $(SRC_DIR_EX)/,	\
				  	expander.c					\
					split.c						\
					)

BASE_SRCS		+= $(addprefix $(SRC_DIR_EXE)/,	\
				  	exec.c						\
					)

BASE_SRCS		+= $(addprefix $(SRC_DIR_LEX)/,	\
				  	lexer.c						\
					)

BASE_SRCS		+= $(addprefix $(SRC_DIR_PAR)/,	\
				  	parser.c					\
				  	validation.c				\
					)

BASE_SRCS		+= $(addprefix $(SRC_DIR_SIG)/,	\
				  	signal.c					\
					)

BASE_SRCS		+= $(addprefix $(SRC_DIR_BU)/,	\
					builtins.c					\
					cd.c						\
					pwd.c						\
					echo.c						\
					env.c						\
					export.c					\
					export_sort.c				\
					unset.c						\
					exit.c						\
					)

BASE_SRCS		+= $(addprefix $(SRC_DIR_UT)/,	\
					cleanup_tools.c				\
					cleanup_tools_2.c			\
					env_tools.c					\
					env_tools_2.c				\
					exec_tools.c				\
					file_tools.c				\
					heredoc_tools.c				\
					heredoc_tools_2.c			\
					init_tools.c				\
					path_tools.c				\
					prompt_tools.c				\
					quote_locate.c				\
					quote_validation.c			\
					redir_locate.c				\
					redir_tools.c				\
					token_tools.c				\
					token_tools_2.c				\
					var_tools.c					\
					var_validation.c			\
					word_locate.c				\
					word_tools.c				\
					)

$(info BASE_SRCS: $(BASE_SRCS))
BASE_OBJS		= $(addprefix $(BUILD_BASE_DIR)/, $(notdir $(patsubst %.c, %.o, $(BASE_SRCS))))
$(info BASE_OBJS: $(BASE_OBJS))

all: $(NAME)

$(NAME): $(BASE_OBJS) $(LIBFT)
	@echo -n "Generating minishell objects... "
	@$(CC) $(CFLAGS) $(BASE_OBJS) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "✅"

$(BUILD_BASE_DIR)/%.o:: $(SRC_DIR)/%.c $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(BUILD_BASE_DIR)/%.o:: $(SRC_DIR_EX)/%.c $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(BUILD_BASE_DIR)/%.o:: $(SRC_DIR_EXE)/%.c $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(BUILD_BASE_DIR)/%.o:: $(SRC_DIR_LEX)/%.c $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(BUILD_BASE_DIR)/%.o:: $(SRC_DIR_PAR)/%.c $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(BUILD_BASE_DIR)/%.o:: $(SRC_DIR_SIG)/%.c $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(BUILD_BASE_DIR)/%.o:: $(SRC_DIR_BU)/%.c $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(BUILD_BASE_DIR)/%.o:: $(SRC_DIR_UT)/%.c $(LIBFT)
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	@echo -n "Cleaning minishell objects... "
	@$(RM) $(BASE_OBJS)
	@echo "✅"
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

fclean: clean
	@echo -n "Cleaning all minishell files... "
	@$(RM) $(BUILD_DIR)
	@$(RM) $(NAME)
	@echo "✅"

re: fclean all

.PHONY: all clean fclean re
