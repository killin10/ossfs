BINS=OssAuth

OssAuth:
	g++ -D__STDC_FORMAT_MACROS OssAuth.cpp ../codec/Base64.cpp ../digest/Hmac.cpp ../util/util.cpp -I ../../include/ -lssl -o $@

clean:
	rm -f $(BINS)
