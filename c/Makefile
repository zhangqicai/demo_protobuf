PROTO_PATH = ../common/
PROTO_FILE = demo.proto 
C_SRC = demo_udp_client.c 

PROTO_SRC = $(basename ${PROTO_FILE}).pb-c.c
PROTO_INC = $(basename ${PROTO_FILE}).pb-c.h

OUTPUT_FILE = $(basename ${C_SRC})

all: ${C_SRC} ${PROTO_SRC}
	gcc ${C_SRC} ${PROTO_SRC} -o build/${OUTPUT_FILE} -lprotobuf-c

${PROTO_SRC}: 
	protoc-c -I=${PROTO_PATH} --c_out=. ${PROTO_FILE}


clean:
	rm -r build/${OUTPUT_FILE}
	rm -r ${PROTO_INC}
	rm -r ${PROTO_SRC}