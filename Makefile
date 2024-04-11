a.out: main.cc
	g++ main.cc -lncurses

clean:
	rm -f a.out core