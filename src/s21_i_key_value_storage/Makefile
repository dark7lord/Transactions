CC			= g++
CCFLAGS		= -Wall -Wextra -Werror -std=c++17
NAME		= s21_i_key_value_storage.a
SRC_DIR		= src/
OBJ_DIR		= obj/
SRC_FILES   = s21_i_key_value_storage.cpp
OBJ_FILES   = $(SRC_FILES:.cpp=.o)
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INC         = s21_i_key_value_storage.h
TEST_DIR	= tests/
TEST_EXE	= run_tests

.PHONY: all clean fclean re tests

all : $(NAME)

$(NAME): $(OBJ) $(INC)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(TEST_DIR)/$(TEST_EXE)

re: fclean $(NAME)

tests: $(NAME)
	$(CC) $(CCFLAGS) $(TEST_DIR)/unit_tests.cpp $(NAME) -l gtest -o $(TEST_DIR)/$(TEST_EXE)
	./$(TEST_DIR)/$(TEST_EXE)
