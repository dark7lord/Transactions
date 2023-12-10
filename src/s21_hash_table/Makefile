CC			 = g++
CCFLAGS		 = -Wall -Wextra -Werror -std=c++17
LDFLAGS		 = -lgtest

NAME		 = s21_hash_table.a

SRC_DIR		 = src/
OBJ_DIR		 = obj/
INC_DIR		 = inc/
TEST_DIR	 = tests/
EXT_DIR		 = ../s21_i_key_value_storage/
EXT_OBJ_DIR  = $(EXT_DIR)obj/

SRC_FILES    = HashTable_core.cpp HashTable.cpp utils.cpp
INC_FILES    = HashTable.h
HEADER		 = s21_hash_table.h
TEST_FILES   = base_functional_unit_tests.cpp core_unit_tests.cpp run_tests.cpp
TEST_EXE	 = run_tests
EXT_LIB		 = s21_i_key_value_storage.a

SRC			 = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			 = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
INC			 = $(addprefix $(INC_DIR), $(INC_FILES)) $(HEADER)
TEST		 = $(addprefix $(TEST_DIR), $(TEST_FILES))

.PHONY: all clean fclean re tests

all : $(EXT_DIR)$(EXT_LIB) $(NAME)

$(EXT_DIR)$(EXT_LIB):
	cd $(EXT_DIR) && make

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ) $(shell ar t $(EXT_DIR)$(EXT_LIB) $(EXT_OBJ_DIR)*.o)
	@echo Compiling $(NAME) success!

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC) $(EXT_DIR)$(EXT_LIB)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	cd $(EXT_DIR) && make clean
	@echo Cleaning obj/ success!

fclean: clean
	rm -f $(NAME)
	cd $(EXT_DIR) && make fclean
	@echo Full cleaning success!

re: fclean all

tests: all
	$(CC) $(CCFLAGS) $(TEST) $(NAME) -o $(TEST_DIR)$(TEST_EXE) $(LDFLAGS)
	./$(TEST_DIR)$(TEST_EXE)
	#leaks -atExit -- ./$(TEST_DIR)$(TEST_EXE)
	rm $(TEST_DIR)$(TEST_EXE)
