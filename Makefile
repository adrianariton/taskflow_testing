TARGETS=para.cpp
INC=./include/
EXEC=para
build:
	g++ $(TARGETS) -std=c++17 -I $(INC) -O2 -pthread -o $(EXEC)
run:
	./$(EXEC)
clean:
	rm $(EXEC)	
