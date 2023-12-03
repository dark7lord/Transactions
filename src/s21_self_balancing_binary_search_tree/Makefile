NAME			:= s21_self_balancing_binary_search_tree
FULL_NAME		:= $(NAME).a

CC				:= g++
CCFLAGS			:= -Wall -Wextra -Werror -std=c++17

SRC_DIR			:= ./
OBJ_DIR			:= obj/
SRC_FILES		:= $(NAME).cpp AVL_Node.cpp
OBJ_FILES		:= $(SRC_FILES:.cpp=.o)
SRC				:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INC				:= $(NAME).h


EXT_LIB_NAME 	:= s21_i_key_value_storage
EXT_LIB_DIR 	:= ../$(EXT_LIB_NAME)
EXT_LIB			:= $(EXT_LIB_DIR)/$(EXT_LIB_NAME).a


.PHONY: all clean fclean re test

all : $(FULL_NAME)

$(EXT_LIB):
	make --silent -C $(EXT_LIB_DIR) && echo ...compiling $(EXT_LIB_NAME)

$(FULL_NAME): $(OBJ) $(INC)
	@make --silent -C $(EXT_LIB_DIR) && echo ...compiling $(EXT_LIB_NAME)
	@ar rcs $(FULL_NAME) $(OBJ) ../s21_i_key_value_storage/obj/s21_i_key_value_storage.o
	@echo Compiling $(FULL_NAME) success!

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I. -I $(EXT_LIB_DIR) -c $< -o $@

test:
	g++ main.cpp AVL_Node.cpp s21_self_balancing_binary_search_tree.cpp -o bst.exe

clean:
	@rm -rf $(OBJ_DIR)
	@echo Cleaning obj/ success!

fclean: clean
	@rm -f $(FULL_NAME)
	@echo Full cleaning success!

re: fclean $(FULL_NAME)
