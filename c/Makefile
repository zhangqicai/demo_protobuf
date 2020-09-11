PROTO_PATH = ../common/
PROTO_FILE = demo.proto 
C_SRC_CLIENT = demo_udp_client.c 
C_SRC_SERVER = demo_udp_server.c

PROTO_SRC = $(basename ${PROTO_FILE}).pb-c.c
PROTO_INC = $(basename ${PROTO_FILE}).pb-c.h

all: udp_server udp_client

udp_client: ${C_SRC_CLIENT} ${PROTO_SRC}
	gcc ${C_SRC_CLIENT} ${PROTO_SRC} -o build/$(basename ${C_SRC_CLIENT}) -lprotobuf-c

udp_server: ${C_SRC_SERVER} ${PROTO_SRC}
	gcc ${C_SRC_SERVER} ${PROTO_SRC} -o build/$(basename ${C_SRC_SERVER}) -lprotobuf-c

${PROTO_SRC}: 
	protoc-c -I=${PROTO_PATH} --c_out=. ${PROTO_FILE}


clean:
	rm -r build/$(basename ${C_SRC_CLIENT})
	rm -r build/$(basename ${C_SRC_SERVER})
	rm -r ${PROTO_INC}
	rm -r ${PROTO_SRC}