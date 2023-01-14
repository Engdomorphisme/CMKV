build:
	g++ -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed *.cc

clean:
	rm -f a.out comp.txt

test-2:
	./a.out data/input/s2-01.txt test.txt
	./a.out data/input/s2-02.txt test.txt
	./a.out data/input/s2-03.txt test.txt
	./a.out data/input/s2-04.txt test.txt
	./a.out data/input/s2-05.txt test.txt
	./a.out data/input/s2-06.txt test.txt
	./a.out data/input/s2-07.txt test.txt
	./a.out data/input/s2-08.txt test.txt
	./a.out data/input/s2-09.txt test.txt

time-test-2:
	time make test-2

test-3:
	./a.out data/input/s3-01.txt test.txt
	./a.out data/input/s3-02.txt test.txt
	./a.out data/input/s3-03.txt test.txt
	./a.out data/input/s3-04.txt test.txt
	./a.out data/input/s3-05.txt test.txt
	./a.out data/input/s3-06.txt test.txt
	./a.out data/input/s3-07.txt test.txt
	./a.out data/input/s3-08.txt test.txt
	./a.out data/input/s3-09.txt test.txt

