TARGETS=lop lexer_test
CALCULATOR_OBJ= add_node.o\
				        ast_node.o\
								ref_env.o\
								binop_node.o\
								calculator_lexer.o\
								calculator_parser.o\
								divide_node.o\
								multiply_node.o\
								number_node.o\
								pow_node.o\
								subtract_node.o\
								ref_node.o\
								assign_node.o\
								if_node.o\
								stop_node.o\
								statements_node.o\
								loop_node.o\
								equal_node.o\
								string_node.o\
								display_node.o\
								input_node.o\
								condition_node.o\
								array_node.o\
								access_node.o\
								hash_node.o\
								function_node.o\
								function_call_node.o\
								array_assign_node.o\
								class_node.o\
								object_create_node.o\
								object_assign_node.o\
								object_access_node.o\
								

#compiler information
LD=g++
CC=g++
CXX=g++
CXXFLAGS=-g -Ilib
LDFLAGS=-Llib
LDLIBS=-lreglex

all: $(TARGETS)
lop: lop.o $(CALCULATOR_OBJ)
lexer_test: lexer_test.o calculator_lexer.o

clean:
	rm -f $(TARGETS) *.o