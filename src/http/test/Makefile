BINS=TestHttp

TestHttp: TestHttp.cpp
	g++ -D__STDC_FORMAT_MACROS ../*.cpp ../../net/*.cpp ../../log/*.cpp ../../util/*.cpp $? -I ../../../include/ -pg -o $@ -lpthread

clean:
	rm -f $(BINS)
