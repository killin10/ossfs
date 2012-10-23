BINS=ossfs

ossfs: main.cpp fs.cpp
	g++ -D__STDC_FORMAT_MACROS -D_FILE_OFFSET_BITS=64  ../oss/*.cpp ../net/*.cpp ../log/*.cpp ../util/*.cpp ../http/*.cpp ../codec/*.cpp ../digest/*.cpp ../xml/*.cpp $? -I ../../include/ -I/usr/include/libxml2 -pg -o $@ -lpthread -lssl -lxml2 -lfuse

clean:
	rm -f $(BINS)
