RES_DIR = resources
DOC_DIR = doc
BUILD_DIR = build
INSTALL_DIR = install
CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra
PROJECT_NAME := C8_3DViewer_v1.0-2
TEST_SRC = back_c/matrix_c/* back_c/*
TEST_SOURCES = test/test.c $(TEST_SRC)



all: install

res:
	mkdir -p $(RES_DIR)

object.a: res
	$(CC) $(CFLAGS) -c back_c/matrix_c/*.c back_c/*.c
	mv *.o $(RES_DIR)/
	ar rcs object.a $(RES_DIR)/*.o
	ranlib object.a
	mv  object.a $(RES_DIR)/


install: uninstall object.a
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../ && make
	cd $(BUILD_DIR) && touch models.txt
	mkdir -p $(INSTALL_DIR)
	mv $(BUILD_DIR)/simple_3d_viewer $(INSTALL_DIR)
ifeq ($(shell uname), Linux)
	chmod 0700 /run/user/1000 
endif
	./$(INSTALL_DIR)/simple_3d_viewer

clean:
	rm -rf $(DOC_DIR) $(RES_DIR) $(BUILD_DIR) coverage_report *.o *.a 3d_viewer tests

uninstall: clean
	rm -rf $(INSTALL_DIR)

dvi:
	mkdir -p $(DOC_DIR)
	doxygen Doxyfile

dist:
	zip -r ../../$(PROJECT_NAME).zip ../../$(PROJECT_NAME)

tests: clean object.a
	$(CC) $(CFLAGS) test/test.c -L. $(RES_DIR)/object.a -o tests -lcheck -lm -lsubunit
	./tests

clang:
	 cp ../materials/linters/.clang-format ./
	 clang-format -i *.h *.cc view/* ctrl_c/* back_c/*.c back_c/*.h back_c/matrix_c/*.c back_c/matrix_c/*.h
	 rm .clang-format

gcov_report: clean res
	$(CC) $(CFLAGS) --coverage -c back_c/matrix_c/*.c back_c/*.c
	mv *.o $(RES_DIR)/
	ar rcs object.a $(RES_DIR)/*.o
	ranlib object.a
	mv object.a $(RES_DIR)/
	$(CC) $(CFLAGS) --coverage test/test.c -L. $(RES_DIR)/object.a  -o tests -lcheck -lm -lsubunit
	./tests
	lcov -c --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	mv *.gcno *.gcda *.info $(RES_DIR)/
