BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: rebuild check 

rebuild: clean_all show_str change_separator binary_div clean

show_str: clean show_str.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) show_str.c -o $(BUILD_PATH)show_str 
	
change_separator: clean change_separator.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) change_separator.c -o $(BUILD_PATH)change_separator 
	
binary_div: clean binary_div.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) binary_div.c -o $(BUILD_PATH)binary_div 

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format *.c *.h common/*.c common/*.h -i
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h common/*.c common/*.h | grep ":"

