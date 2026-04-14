testcplx: testcplx.o
	g++ -g -Wall $^ -o $@

testcplx.o: testcplx.cpp complex.h
	g++ -g -c -Wall $< -o $@

.PHONY: clean

clean:
	-rm testcplx.o testcplx
