

NAME    = nanopb-simple
PROTOC-BIN-LOC := ..\nanopb\generator-bin

CPP_SRC     += \
			src/main.cpp
			
NBINCLUDE	+= \
			-I../Library

XTRALIB 	+= \
			../Library/obj/release/libnanopb.a

CREATEDTARGS += src/simple.pb.h src/simple.pb.c
C_SRC +=src/simple.pb.c

all: build-library generate-proto-source $(TARGET)

generate-proto-source: 
	$(PROTOC-BIN-LOC)\protoc.exe --nanopb_out=. --proto_path=src simple.proto
	mv simple.pb.c src/
	mv simple.pb.h src/

build-library:
	make -C ..\Library

clean-all:
	make -C ..\Library clean
	make clean

include $(NNDK_ROOT)/make/boilerplate.mk
