CC			= g++
CCFLAGS		= -Wall -Wextra -Werror -std=c++17
NAME		= s21_i_key_value_storage.a
SRC_DIR		= ./
OBJ_DIR		= obj/
SRC_FILES   = s21_i_key_value_storage.cpp
OBJ_FILES   = $(SRC_FILES:.cpp=.o)
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INC         = s21_i_key_value_storage.h

.PHONY: all clean fclean re test

all : $(NAME)

$(NAME): $(OBJ) $(INC)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) a.out

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
