linked_music_lib: project1.o project1_impl.o project1.h
	g++ -Wall -std=c++11 -g project1.o project1_impl.o -o linked_music_lib

project1_impl.o: project1_impl.cpp project1.h
	g++ -Wall -std=c++11 -c -g project1_impl.cpp

project1.o: project1.cpp project1.h
	g++ -Wall -std=c++11 -c -g project1.cpp

clean:
	rm linked_music_lib *.o
