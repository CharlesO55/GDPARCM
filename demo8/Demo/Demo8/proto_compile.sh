#!/bin/bash
# directory of protoc: X:/GithubProjects/vcpkg/packages/protobuf_x64-windows/tools/protobuf

#where protobuf.exe and grpc_cpp_plugin.exe are
#PROTOC_DIR="X:/GithubProjects/vcpkg/packages/protobuf_x64-windows/tools/protobuf"
#GRPC_CPP_EXE="X:/GithubProjects/vcpkg/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe"

PROTOC_DIR="D:/GDPARCM/demo8/Demo/vcpkg/packages/protobuf_x64-windows/tools/protobuf"
GRPC_CPP_EXE="D:/GDPARCM/demo8/Demo/vcpkg/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe"


#where your .proto files are
#SRC_DIR="D:/Documents/GithubProjects/GDADPRG-GDPARCM_Courseware/GDPARCM_HO8-gRPCDemo/"
#DST_DIR="D:/Documents/GithubProjects/GDADPRG-GDPARCM_Courseware/GDPARCM_HO8-gRPCDemo/"

SRC_DIR="D:/GDPARCM/demo8/Demo/Demo8/"
DST_DIR="D:/GDPARCM/demo8/Demo/Demo8/"



echo "Src Directory: $SRC_DIR"
echo "Dst Directory: $DST_DIR"

$PROTOC_DIR/protoc --proto_path=$SRC_DIR --cpp_out=$DST_DIR --grpc_out=$DST_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_EXE $SRC_DIR/helloworld.proto

$SHELL