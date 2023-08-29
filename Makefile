all: main.o VideoProcessor.o
	g++ -o VideoProcessorApp main.o VideoProcessor.o -lpthread

main.o: main.cpp VideoProcessor.h
	g++ -c main.cpp

VideoProcessor.o: VideoProcessor.cpp VideoProcessor.h
	g++ -c VideoProcessor.cpp

clean:
	rm -f *.o VideoProcessorApp

