# NAME:=		main.exe
EXEC:=		main.exe
TEST_EXEC:= tests.exe

CXX:=		g++
CXXFLAGS:=	-Wall -Wextra -Werror -std=c++17
LDFLAGS := -lgcov -pthread

GCOV_REPORT := coverage.info

SRC := main.cpp
OBJS := $(SRC:.cpp=.o)
TEST_SRC := tests/test.cpp tests/bin_tree.test.cpp
TEST_OBJS := $(TEST_SRC:.cpp=.o)


# Paths libs
KEY_VALUE_STORAGE_PATH:=	./s21_i_key_value_storage
HASH_TABLE_PATH:=			./s21_hash_table
BIN_TREE_PATH:=				./s21_self_balancing_binary_search_tree

# Names libs
KEY_VALUE_STORAGE_NAME:= 	s21_i_key_value_storage
HASH_TABLE_NAME:=			s21_hash_table
BIN_TREE_NAME:=				s21_self_balancing_binary_search_tree

HEADERS_LIBS :=				-I ./s21_self_balancing_binary_search_tree\
							-I ./s21_hash_table

# Full names libs
HASH_TABLE:=				$(HASH_TABLE_PATH)/$(HASH_TABLE_NAME).a
BIN_TREE:=					$(BIN_TREE_PATH)/$(BIN_TREE_NAME).a
KEY_VALUE_STORAGE:=			$(KEY_VALUE_STORAGE_PATH)/$(KEY_VALUE_STORAGE_NAME).a

LIBS:= $(HASH_TABLE) $(BIN_TREE)

.PHONY: all run fclean re test storage bin_tree hash_tree coverage html

all: $(EXEC)

storage:
	@make --silent -C $(KEY_VALUE_STORAGE_PATH) && echo ...compiling $(KEY_VALUE_STORAGE_NAME)

bin_tree:
	@make --silent -C $(BIN_TREE_PATH) && echo ...compiling $(BIN_TREE_NAME)

hash_table:
	@make --silent -C $(HASH_TABLE_PATH) && echo ...compiling $(HASH_TABLE_NAME)

$(EXEC): storage bin_tree hash_tree
	$(CXX) $(CXXFLAGS) main.cpp $(HASH_TABLE) $(BIN_TREE) \
		-I $(HASH_TABLE_PATH) \
		-I $(BIN_TREE_PATH) \
		-o main.exe && echo Compiling success!

$(TEST_EXEC): bin_tree hash_table $(TEST_OBJS) $(OBJS)
	$(CXX) $(TEST_OBJS) $(OBJS) $(HEADERS_LIBS) $(LIBS) -o $(TEST_EXEC) $(LDFLAGS)

run: $(EXEC)
	./$(EXEC)

test: CXXFLAGS += -fprofile-arcs -ftest-coverage
test: LDFLAGS += -fprofile-arcs -ftest-coverage
test: $(TEST_EXEC)
	./$(TEST_EXEC)

tests: $(BIN_TREE)
	@$(CXX) $(CXXFLAGS) tests/test.cpp tests/bin_tree.test.cpp $(BIN_TREE) -I $(BIN_TREE_PATH) -o test.exe -lgtest
	@./test.exe
	@rm test.exe

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS_LIBS) -c $< -o $@

coverage: test
	gcov $(SRC)
	lcov --capture --directory . --output-file $(GCOV_REPORT)

clean:
#cd ./s21_hash_table && make clean
	@make --silent -C $(HASH_TABLE_PATH)		clean && echo ...clean $(HASH_TABLE_NAME)
	@make --silent -C $(BIN_TREE_PATH)			clean && echo ...clean $(BIN_TREE_NAME)
	@make --silent -C $(KEY_VALUE_STORAGE_PATH) clean && echo ...clean $(KEY_VALUE_STORAGE_NAME)
	@echo Cleaning success!

fclean:
	@make --silent -C $(HASH_TABLE_PATH) 		fclean && echo ...full clean $(HASH_TABLE_NAME)
	@make --silent -C $(BIN_TREE_PATH) 			fclean && echo ...full clean $(BIN_TREE_NAME)
	@make --silent -C $(KEY_VALUE_STORAGE_PATH) fclean && echo ...full clean $(KEY_VALUE_STORAGE)
	@rm -rf $(EXEC)
	@echo Full cleaning success!

re: fclean all
