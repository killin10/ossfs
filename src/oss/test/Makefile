BINS=TestOss TestListObjects TestPutObject TestHeadObject TestDelObject

TestOss: TestOss.cpp
	g++ -D__STDC_FORMAT_MACROS ../*.cpp ../../net/*.cpp ../../log/*.cpp ../../util/*.cpp ../../http/*.cpp ../../codec/*.cpp ../../digest/*.cpp ../../xml/*.cpp $? -I ../../../include/ -I/usr/include/libxml2 -pg -o $@ -lpthread -lssl -lxml2

TestListObjects: TestListObjects.cpp
	g++ -D__STDC_FORMAT_MACROS ../*.cpp ../../net/*.cpp ../../log/*.cpp ../../util/*.cpp ../../http/*.cpp ../../codec/*.cpp ../../digest/*.cpp ../../xml/*.cpp $? -I ../../../include/ -I/usr/include/libxml2 -pg -o $@ -lpthread -lssl -lxml2


TestPutObject: TestPutObject.cpp
	g++ -D__STDC_FORMAT_MACROS ../*.cpp ../../net/*.cpp ../../log/*.cpp ../../util/*.cpp ../../http/*.cpp ../../codec/*.cpp ../../digest/*.cpp ../../xml/*.cpp $? -I ../../../include/ -I/usr/include/libxml2 -pg -o $@ -lpthread -lssl -lxml2

TestHeadObject: TestHeadObject.cpp
	g++ -D__STDC_FORMAT_MACROS ../*.cpp ../../net/*.cpp ../../log/*.cpp ../../util/*.cpp ../../http/*.cpp ../../codec/*.cpp ../../digest/*.cpp ../../xml/*.cpp $? -I ../../../include/ -I/usr/include/libxml2 -pg -o $@ -lpthread -lssl -lxml2

TestDelObject: TestDelObject.cpp
	g++ -D__STDC_FORMAT_MACROS ../*.cpp ../../net/*.cpp ../../log/*.cpp ../../util/*.cpp ../../http/*.cpp ../../codec/*.cpp ../../digest/*.cpp ../../xml/*.cpp $? -I ../../../include/ -I/usr/include/libxml2 -pg -o $@ -lpthread -lssl -lxml2

clean:
	rm -f $(BINS)
