all: check test

check:
	clang-format src/*.c src/*.h src/common/*.c src/common/*.h -i
	cppcheck --enable=all --suppress=missingIncludeSystem src/*.c src/*.h src/common/*.c src/common/*.h

test:
	pytest --color=yes -v --tb=short  

test_config:
	python3 -m venv test-env  
	source test-env/bin/activate 
	pip install -r tests/requirements.txt



