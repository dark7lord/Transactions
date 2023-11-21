.PHONY: all run fclean re

all : 
	cd ./s21_hash_table && make
	g++ main.cpp s21_hash_table/s21_hash_table.a -o main

run :
	./main

clean:
	cd ./s21_hash_table && make clean
	cd ./s21_i_key_value_storage && make clean
	rm -rf main

fclean:
	cd ./s21_hash_table && make fclean
	cd ./s21_i_key_value_storage && make fclean
	rm -rf main

re: fclean all
