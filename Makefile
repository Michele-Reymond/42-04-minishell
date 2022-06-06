# For compilers to find readline you may need to set:
# export LDFLAGS="-L/Users/vroch/.brew/opt/readline/lib"
# export CPPFLAGS="-I/Users/vroch/.brew/opt/readline/include"


NAME = minishell
CC = gcc
FLAGS = -g3 -Wall -Wextra -Werror
INC = -I inc -I src/libft/inc -I$(HOME)/.brew/opt/readline/include
LFT = -L src/libft -lft -lreadline -L$(HOME)/.brew/opt/readline/lib

SRC_NAME = 	minishell.c \
			ms_builtins.c \
			ms_b_echo.c \
			ms_b_tabs.c \
			ms_b_tabsort.c \
			ms_b_variables.c \
			ms_b_var_utils.c \
			ms_b_export.c \
			ms_b_cd.c \
			ms_b_pwd.c \
			ms_b_other.c \
			ms_parsing.c \
			ms_pipes.c \
			ms_errors.c


OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

LIB_DIR = src/libft/
SRC_DIR = src/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent 
	@gcc -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft -lreadline
	@echo "##### minishell compiling finished! #####"
	@echo "   (¯\`v´¯)"
	@echo "  (¯\`(█)´¯)  (¯\`v´¯)"
	@echo "   (_.^._)  (¯\`(█)´¯)"
	@echo "     (¯\`v´¯)´(_.^._)"
	@echo "    (¯\`(█)´¯)(¯\`v´¯)"
	@echo "     (_.^._)(¯\`(█)´¯)"
	@echo " (¯\`v´¯)     (_.^._)"
	@echo "(¯\`(█)´¯) "
	@echo " (_.^._)  FLOWERS Team"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@gcc $(FLAGS) -o $@ -c $< $(INC) 

run:
	./$(NAME)

clean:
	@make -C $(LIB_DIR) clean --silent
	@rm -f $(OBJ)
	@echo "##### Removed object files #####"

fclean: clean
	@make -C $(LIB_DIR) fclean --silent
	@rm -f $(NAME)
	@echo "##### Removed binary files #####"

re: fclean all

.PHONY: all clean fclean re run
