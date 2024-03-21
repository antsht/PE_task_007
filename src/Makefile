BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: rebuild check 

rebuild: clean_all show_str change_separator binary_div real_db clean

show_str: clean show_str.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) show_str.c sqlite3/sqlite3.o -o $(BUILD_PATH)show_str 
	
change_separator: clean change_separator.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) change_separator.c -o $(BUILD_PATH)change_separator 
	
binary_div: clean binary_div.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) binary_div.c -o $(BUILD_PATH)binary_div 
	
real_db: clean real_db.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) real_db.c real_db/ui.c real_db/db_layer.c real_db/students_record.c common/errors.c common/logger.c sqlite3/sqlite3.o -o $(BUILD_PATH)real_db

#sqlite3: sqlite3/sqlite3.o
#	$(CC) -lpthread -ldl -o sqlite3/sqlite3.o -c sqlite3/sqlite3.c

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format *.c *.h common/*.c common/*.h real_db/*.c real_db/*.h -i
	cppcheck --enable=all --force --suppress=missingIncludeSystem  -U SQLITE_INT64_TYPE *.c *.h common/*.c common/*.h real_db/*.c real_db/*.h
