NAME = minishell
FLAGS = -Wall -Wextra -Werror
INC = -Iincludes/ -I$(LIB_DIR)/includes 

SRC_NAME = 	minishell.c \
			ms-b-echo.c

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

LIB_DIR = src/libft/
SRC_DIR = src/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent 
	@gcc -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft
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
