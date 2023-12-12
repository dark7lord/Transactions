NAME			:= s21_self_balancing_binary_search_tree.a

CC				:= g++
CCFLAGS			:= -Wall -Wextra -Werror -std=c++17
LDFLAGS			:= -lgtest

SRC_DIR			:= src/
OBJ_DIR			:= obj/
INC_DIR			:= inc/
TEST_DIR		:= tests/
EXT_DIR			:= ../s21_i_key_value_storage/
EXT_OBJ_DIR		:= $(EXT_DIR)obj/

SRC_FILES		:= s21_self_balancing_binary_search_tree.cpp Node.cpp
OBJ_FILES		:= $(SRC_FILES:.cpp=.o)
INC_FILES		:= Node.h
HEADER			:= s21_self_balancing_binary_search_tree.h
TEST_FILES		:= run_tests.cpp
TEST_EXE		:= bst.exe
EXT_LIB			:= s21_i_key_value_storage.a

SRC				:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INC				:= $(addprefix $(INC_DIR), $(INC_FILES)) $(HEADER)
TEST			:= $(addprefix $(TEST_DIR), $(TEST_FILES))

.PHONY: all clean fclean re tests run_test

all : $(EXT_DIR)$(EXT_LIB) $(NAME) $()

$(EXT_DIR)$(EXT_LIB):
	make --silent -C $(EXT_DIR) && echo ...compiling $(EXT_LIB)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(shell ar t $(EXT_DIR)$(EXT_LIB) $(EXT_OBJ_DIR)*.o)
	@echo Compiling $(NAME) success!

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC) $(EXT_DIR)$(EXT_LIB)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

tests: all
	@$(CC) $(CCFLAGS) $(TEST) $(NAME) -o $(TEST_DIR)$(TEST_EXE) $(LDFLAGS)
	./$(TEST_DIR)$(TEST_EXE)
#	leaks -atExit -- ./$(TEST_DIR)$(TEST_EXE)
	rm $(TEST_DIR)$(TEST_EXE)

clean:
	@rm -rf $(OBJ_DIR)
	@cd $(EXT_DIR) && make clean
	@echo Cleaning obj/ success!

fclean: clean
	@rm -f $(NAME) $(TEST_DIR)$(TEST_EXE)
	@cd $(EXT_DIR) && make fclean
	@echo Full cleaning success!

re: fclean $(FULL_NAME) all $(TARGET_TEST)


 clang_n:
 	clang-format -style=Google -n *.c *.h
# clang_i:
# 	clang-format -style=Google -i *.c *.h
