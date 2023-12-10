# set $LIBRARY_PATH to place where libgtest.a is located
# set $CPLUS_INCLUDE_PATH to place where gtest/gtest.h is located

NAME:=		main.exe

CC:=		g++
CCFLAGS:=	-Wall -Wextra -Werror -std=c++17

SRC_DIR:= s21_key_value_console_interface/src/
SRC_FILES:= KeyValueConsoleInterface_management.cpp KeyValueConsoleInterface_navigation.cpp parsing_utils.cpp
MAIN:= main.cpp
INC_DIR := s21_key_value_console_interface/
INC:= $(INC_DIR)s21_key_value_console_interface.h
SRC:= $(addprefix $(SRC_DIR), $(SRC_FILES)) $(MAIN)

# Paths libs
KEY_VALUE_STORAGE_PATH:=	./s21_i_key_value_storage
HASH_TABLE_PATH:=			./s21_hash_table
BIN_TREE_PATH:=				./s21_self_balancing_binary_search_tree

# Names libs
KEY_VALUE_STORAGE_NAME:= 	s21_i_key_value_storage
HASH_TABLE_NAME:=			s21_hash_table
BIN_TREE_NAME:=				s21_self_balancing_binary_search_tree

# Full names libs
HASH_TABLE:=				$(HASH_TABLE_PATH)/$(HASH_TABLE_NAME).a
BIN_TREE:=					$(BIN_TREE_PATH)/$(BIN_TREE_NAME).a
KEY_VALUE_STORAGE:=			$(KEY_VALUE_STORAGE_PATH)/$(KEY_VALUE_STORAGE_NAME).a

.PHONY: all run fclean clean re tests check_ext

all: check_ext $(NAME)
	@echo Compiling success!

check_ext:
	@echo ...compiling $(KEY_VALUE_STORAGE_NAME) && make --silent -C $(KEY_VALUE_STORAGE_PATH)
	@echo ...compiling $(BIN_TREE_NAME)          && make --silent -C $(BIN_TREE_PATH)
	@echo ...compiling $(HASH_TABLE_NAME)        && make --silent -C $(HASH_TABLE_PATH)


$(NAME): $(KEY_VALUE_STORAGE) $(BIN_TREE) $(HASH_TABLE) $(SRC) $(INC)
	$(CC) $(CCFLAGS) $(SRC) $(HASH_TABLE) $(BIN_TREE) $(KEY_VALUE_STORAGE) -I $(INC_DIR) -I $(HASH_TABLE_PATH) -I $(BIN_TREE_PATH) -I $(KEY_VALUE_STORAGE_PATH) -o $(NAME)

run: all
	./$(NAME)

clean:
#cd ./s21_hash_table && make clean
	@echo ...clean $(KEY_VALUE_STORAGE_NAME) && make --silent -C $(KEY_VALUE_STORAGE_PATH) clean
	@echo ...clean $(HASH_TABLE_NAME) && make --silent -C $(HASH_TABLE_PATH) clean
	@echo ...clean $(BIN_TREE_NAME) && make --silent -C $(BIN_TREE_PATH)     clean
	@echo Cleaning success!

fclean:
	@echo ...full clean $(KEY_VALUE_STORAGE_NAME) && make --silent -C $(KEY_VALUE_STORAGE_PATH) fclean
	@echo ...full clean $(HASH_TABLE_NAME) && make --silent -C $(HASH_TABLE_PATH) fclean
	@echo ...full clean $(BIN_TREE_NAME)   && make --silent -C $(BIN_TREE_PATH)   fclean
	@rm -rf $(NAME)
	@echo Cleaning is over.

re: fclean all

tests: all
	@make --silent -C $(KEY_VALUE_STORAGE_PATH) tests
	@make --silent -C $(HASH_TABLE_PATH) tests
	@make --silent -C $(BIN_TREE_PATH) tests