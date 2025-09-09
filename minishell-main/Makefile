# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 17:31:34 by erazumov          #+#    #+#              #
#    Updated: 2025/09/09 18:42:09 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                 Informations                                 #
# ============================================================================ #
NAME = minishell
CC = cc
RM = rm -f

# ============================================================================ #
#                                   Flags                                      #
# ============================================================================ #
CFLAGS = -Wall -Wextra -Werror -g

# ============================================================================ #
#                                 Dossiers                                     #
# ============================================================================ #
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
INCLUDE_DIR = include

# ============================================================================ #
#                         Listes des fichiers sources (manuel)                 #
# ============================================================================ #
CORE_FILES = input.c syntax_checker.c
LEXER_FILES = lexer.c lexer_handlers.c lexer_token_utils.c lexer_clean_word.c \
			  lexer_word_utils.c
PARSER_FILES = parser.c parser_loop.c parser_list_utils.c \
			   parser_free.c parser_built_utils.c
EXPANSION_FILES = expansion.c expansion_str.c expansion_handlers.c \
				  expansion_len_utils.c expansion_var_utils.c \
				  expansion_append_utils.c
EXEC_FILES = execution.c execution_utils.c pipeline.c pipeline_utils.c \
			 process_utils.c redirections.c path.c env_utils.c env_set.c \
			 env_unset.c heredoc.c heredoc_utils.c children.c heredoc_single.c
SIGNALS_FILES = signals.c
BUILTINS_FILES = builtin_cd.c builtin_echo.c builtin_env.c builtin_export.c \
				 builtin_export_utils.c builtin_exit.c builtin_pwd.c \
				 builtin_unset.c builtin_exit_utils.c
UTILS_FILES = title.c text.c
DEBUG_FILES = debug_commands.c debug_tokens.c

# ============================================================================ #
#                  Construction des chemins et des objets                      #
# ============================================================================ #
MAIN_SRC = $(SRC_DIR)/main.c prompt.c
CORE_SRC = $(addprefix $(SRC_DIR)/core/, $(CORE_FILES))
LEXER_SRC = $(addprefix $(SRC_DIR)/lexer/, $(LEXER_FILES))
PARSER_SRC = $(addprefix $(SRC_DIR)/parser/, $(PARSER_FILES))
EXPANSION_SRC = $(addprefix $(SRC_DIR)/expansion/, $(EXPANSION_FILES))
EXEC_SRC = $(addprefix $(SRC_DIR)/execution/, $(EXEC_FILES))
SIGNALS_SRC = $(addprefix $(SRC_DIR)/signals/, $(SIGNALS_FILES))
BUILTINS_SRC = $(addprefix $(SRC_DIR)/execution/builtins/, $(BUILTINS_FILES))
UTILS_SRC = $(addprefix $(SRC_DIR)/utils/, $(UTILS_FILES))
DEBUG_SRC = $(addprefix $(SRC_DIR)/debug/, $(DEBUG_FILES))

SRC = $(MAIN_SRC) $(CORE_SRC) $(LEXER_SRC) $(PARSER_SRC) $(EXPANSION_SRC) \
	  $(EXEC_SRC) $(SIGNALS_SRC) $(BUILTINS_SRC) $(UTILS_SRC) $(DEBUG_SRC)\

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

DEPS = $(OBJS:.o=.d)

# ============================================================================ #
#                                Bibliothèques                                 #
# ============================================================================ #
READLINE_PATH = /opt/homebrew/opt/readline

INCLUDES = -I $(INCLUDE_DIR) -I $(LIBFT_DIR)/include -I $(READLINE_PATH)/include
LDFLAGS = -L $(LIBFT_DIR) -L $(READLINE_PATH)/lib -lft -lreadline
LIBFT = $(LIBFT_DIR)/libft.a

# ============================================================================ #
#                                    Règles                                    #
# ============================================================================ #
all: $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "\033[0;32m✅ Minishell is ready!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[0;33m✨ Compiling:\033[0m $<"

-include $(DEPS)

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -s -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@echo "\033[0;31m🗑️  Executables minishell removed\033[0m"

re: fclean all

norm:
	@norminette $(SRC_DIR) $(LIBFT_DIR) include/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
