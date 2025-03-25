#!/bin/bash
CURR_DIR=$(dirname "$(realpath "$0")")
VCPKG_DIR=$(realpath "$CURR_DIR/../../vcpkg")

#where protobuf.exe and grpc_cpp_plugin.exe are
PROTOC_DIR="$VCPKG_DIR/packages/protobuf_x64-windows/tools/protobuf"
echo "Protoc Directory: $PROTOC_DIR"

GRPC_CPP_EXE="$VCPKG_DIR/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe"
echo "GRPC Plugin Directory: $GRPC_CPP_EXE"




#where your .proto files are
SRC_DIR=$CURR_DIR
echo "Src Directory: $SRC_DIR"

DST_DIR=$CURR_DIR
echo "Dst Directory: $DST_DIR"


#PROTO_FILE="SceneViewer.proto"
PROTO_FILE="helloworld.proto"

echo "Proto Filename: $PROTO_FILE"


$PROTOC_DIR/protoc --proto_path=$SRC_DIR --cpp_out=$DST_DIR --grpc_out=$DST_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_EXE $SRC_DIR/$PROTO_FILE

$SHELL