NAME:=		main
OUTPUT:=	$(NAME).exe

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

.PHONY: all run fclean re test

all :
	@make --silent -C $(HASH_TABLE_PATH) && echo ...compiling $(HASH_TABLE_NAME)
	@make --silent -C $(BIN_TREE_PATH) && echo ...compiling $(BIN_TREE_NAME)
	@g++ main.cpp $(HASH_TABLE) $(BIN_TREE) \
		-I $(HASH_TABLE_PATH) \
		-I $(BIN_TREE_PATH) \
		-o main.exe && echo Compiling success!

run :
	./$(OUTPUT)


clean:
#cd ./s21_hash_table && make clean
	@make --silent -C $(HASH_TABLE_PATH) 		clean && echo ...clean $(HASH_TABLE_NAME)
	@make --silent -C $(BIN_TREE_PATH) 			clean && echo ...clean $(BIN_TREE_NAME)
	@make --silent -C $(KEY_VALUE_STORAGE_PATH) clean && echo ...clean $(KEY_VALUE_STORAGE_NAME)
	@echo Cleaning success!
#cd ./s21_i_key_value_storage && make clean
# rm -rf main

fclean:
	@make --silent -C $(HASH_TABLE_PATH) 		fclean && echo ...full clean $(HASH_TABLE_NAME)
	@make --silent -C $(BIN_TREE_PATH) 			fclean && echo ...full clean $(BIN_TREE_NAME)
	@make --silent -C $(KEY_VALUE_STORAGE_PATH) fclean && echo ...full clean $(KEY_VALUE_STORAGE)
#	cd ./s21_hash_table && make fclean
#	cd ./s21_i_key_value_storage && make fclean
	@rm -rf $(OUTPUT)
	@echo Full cleaning success!

re: fclean all
