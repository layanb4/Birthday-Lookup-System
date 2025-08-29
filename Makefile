all: test1

test1: a4_birthdayLookupSystem.cpp a4_birthdaylib.cpp a4_birthdayBST.cpp
	//you can uncomment this one to check for memory leaks
	//g++ -Wall -std=c++11 -fsanitize=leak -o test1 a4_birthdayLookupSystem.cpp a4_birthdaylib.cpp a4_birthdayBST.cpp
	g++ -Wall -std=c++11 -o test1 a4_birthdayLookupSystem.cpp a4_birthdaylib.cpp a4_birthdayBST.cpp


clean:
	rm -f test1
