build:
	g++ -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed *.cc

clean:
	rm -f a.out comp.txt