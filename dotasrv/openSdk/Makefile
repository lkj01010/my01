top_path := $(shell pwd | awk -F ' ' {print$1})
dest_outlib_dir := $(top_path)/outlib

openssl:=package_compile/openssl-0.9.8r
openssl_clean:=$(openssl)

curl:=package_compile/curl-7.30.0
curl_clean:=$(curl)

oauth:=package_compile/liboauth-0.9.4
oauth_clean:=$(oauth)
scons:= package_compile/scons-2.3.0
jsoncpp:=package_compile/jsoncpp-src-0.5.0
jsoncpp_clen=$(jsoncpp)

tencent_sdk_lib:=tencent_sdk_lib
tencent_sdk_lib_clean= $(tencent_sdk_lib)

example:=example
example_clean:=$(example)

export INC_JSON :=-I$(dest_outlib_dir)/jsoncpp/include
export LIB_JSON :=-L$(dest_outlib_dir)/jsoncpp/lib -ljson

export INC_OPENSSL:=-I$(dest_outlib_dir)/openssl/include
export LIB_OPENSSL:=-L$(dest_outlib_dir)/openssl/lib -lssl -lcrypto

export INC_OAUTH:=-I$(dest_outlib_dir)/oauth/include
export LIB_OAUTH:=-L$(dest_outlib_dir)/oauth/lib -loauth

export INC_CURL:=-I$(dest_outlib_dir)/curl/include
export LIB_CURL:=-L$(dest_outlib_dir)/curl/lib  -lcurl

export INC_OPENAPI:=-I$(top_path)/$(tencent_sdk_lib)/include
export LIB_OPENAPI:=-L$(top_path)/$(tencent_sdk_lib)/lib -lopenapi

.PHONY: outlib openssl curl oauth jsoncpp tencent_sdk_lib example
outlib: openssl curl oauth jsoncpp tencent_sdk_lib



example:
	$(MAKE) --directory=$($@) all

openssl:
	$(MAKE) --directory=$($@) install &&\
	cp $(dest_outlib_dir)/openssl/lib/libssl.a /usr/lib/libssl.a &&\
	cp $(dest_outlib_dir)/openssl/lib/libcrypto.a /usr/lib/libcrypto.a &&\
	echo -e "\033[41;36m  openssl cp oooooooooooooooooooooooooo \033[0m"
	
curl: openssl
	$(MAKE) LDFLAGS+=-ldl --directory=$($@) install &&\
	cp $(dest_outlib_dir)/curl/lib/libcurl.a /usr/lib/libcurl.a &&\
	echo -e "\033[41;36m  curl cp oooooooooooooooooooooooooo \033[0m"
	
oauth:openssl
	$(MAKE) --directory=$($@) install &&\
	cp $(dest_outlib_dir)/oauth/lib/liboauth.a /usr/lib/liboauth.a &&\
	echo -e "\033[41;36m  oauth cp oooooooooooooooooooooooooo \033[0m"

jsoncpp:
	cd  $(top_path)/$(jsoncpp) && \
	python ../scons-2.3.0/script/scons platform=linux-gcc&& \
	mkdir -p $(dest_outlib_dir)/jsoncpp/include&& \
	mkdir -p $(dest_outlib_dir)/jsoncpp/lib&& \
	cp 	include/*  $(dest_outlib_dir)/jsoncpp/include -rf&& \
	find libs/ -name *.a  -type f |xargs -IX cp X $(dest_outlib_dir)/jsoncpp/lib/libjson.a &&\
	echo -e "\033[41;36m  jsoncpp finish oooooooooooooooooooooooooo \033[0m"


tencent_sdk_lib:
	echo -e "\033[41;36m  tencent_sdk_lib want to start oooooooooooooooooooooooooo \033[0m"
	$(MAKE) --directory=$($@) all

	
config: openssl_config curl_config oauth_config

openssl_config:
	cd $(openssl) && \
	 chmod u+x ./config &&\
	./config --prefix=$(dest_outlib_dir)/openssl
	
curl_config:
	cd $(curl) && \
	chmod u+x ./configure &&\
	./configure --prefix=$(dest_outlib_dir)/curl --without-zlib --enable-shared=no --with-ssl=$(dest_outlib_dir)/openssl

oauth_config:
	cd $(oauth) && \
	chmod u+x ./configure&&\
	./configure --prefix=$(dest_outlib_dir)/oauth  --disable-libcurl --enable-shared=no  CFLAGS=-I$(dest_outlib_dir)/openssl/include/ LDFLAGS=-L$(dest_outlib_dir)/openssl/lib


.PHONY: clean openssl_clean curl_clean oauth_clean tencent_sdk_lib_clean example_clean
clean: openssl_clean curl_clean oauth_clean tencent_sdk_lib_clean example_clean
openssl_clean curl_clean oauth_clean tencent_sdk_lib_clean  example_clean:
	$(MAKE) --directory=$($@) clean
