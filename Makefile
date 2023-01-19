build:
	g++ -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed *.cc

clean:
	rm -f a.out comp.txt

test_given:
	./test_given.sh

test_create:
	./test.sh 2
	./test.sh 3
	./test.sh 4
	./test.sh 5
	./test.sh 6