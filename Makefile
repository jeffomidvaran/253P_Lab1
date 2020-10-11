CXXFLAGS= -ggdb -std=c++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant

main: lab1.cpp
	@clear
	@c++ $(CSSFLAGS) lab1.cpp
	@./a.out 10
	@rm a.out
	

