GPP=g++
TESTS_DIR=.
O_FILES_DIR=$(TESTS_DIR)/oFiles
EXEC=InOutTester
TESTS_INCLUDED_FILE=../worldcup23a2.h
OBJS=$(O_FILES_DIR)/main23a2.o $(O_FILES_DIR)/worldcup23a2.o $(O_FILES_DIR)/UnionFind.o $(O_FILES_DIR)/HashTable.o $(O_FILES_DIR)/Player.o $(O_FILES_DIR)/Team.o $(O_FILES_DIR)/Tuple.o 
DEBUG_FLAG= -g# can add -g
COMP_FLAG=--std=c++11 -Wall -Werror -pedantic-errors $(DEBUG_FLAG)

$(EXEC) : $(OBJS)
	$(GPP) $(COMP_FLAG) $(OBJS) -o $@

$(O_FILES_DIR)/UnionFind.o : ../UnionFind.cpp ../UnionFind.h
	$(GPP) -c $(COMP_FLAG) ../UnionFind.cpp -o $@

$(O_FILES_DIR)/HashTable.o : ../HashTable.cpp ../HashTable.h ../Player.h
	$(GPP) -c $(COMP_FLAG) ../HashTable.cpp -o $@

$(O_FILES_DIR)/Tuple.o : ../Tuple.cpp ../Tuple.h
	$(GPP) -c $(COMP_FLAG) ../Tuple.cpp -o $@

$(O_FILES_DIR)/main23a2.o : $(TESTS_DIR)/main23a2.cpp $(TESTS_INCLUDED_FILE)
	$(GPP) -c $(COMP_FLAG) $(TESTS_DIR)/main23a2.cpp -o $@

$(O_FILES_DIR)/worldcup23a2.o : ../worldcup23a2.cpp ../wet2util.h ../AVLTree.h ../UnionFind.h ../HashTable.h ../Player.h ../Team.h ../Tuple.h
	$(GPP) -c $(COMP_FLAG) ../worldcup23a2.cpp -o $@

$(O_FILES_DIR)/Player.o : ../Player.cpp ../Player.h ../Team.h ../UnionFind.h
	$(GPP) -c $(COMP_FLAG) ../Player.cpp -o $@

$(O_FILES_DIR)/Team.o : ../Team.cpp ../Team.h ../UnionFind.h
	$(GPP) -c $(COMP_FLAG) ../Team.cpp -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)