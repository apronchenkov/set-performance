CXXFLAGS = -O3 -std=c++11 -DNDEBUG

.PHONY: all clean

all: sequential_insert.png random_insert_16384.png random_insert.png

clean:
	$(RM) \
		sequential_insert sequential_insert.log sequential_insert.png \
		random_insert_16384 random_insert_16384.log random_insert_16384.png \
		random_insert random_insert.log random_insert.png

sequential_insert: sequential_insert.cpp

random_insert_16384: random_insert_16384.cpp

random_insert: random_insert.cpp

sequential_insert.log: sequential_insert
	./sequential_insert > "$@"

random_insert_16384.log: random_insert_16384
	./random_insert_16384 > "$@"

random_insert.log: random_insert
	./random_insert > "$@"

%.png: %.log
	gnuplot $(basename $@).plot
