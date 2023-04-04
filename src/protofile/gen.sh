protoc $2 --proto_path=$1/src/protofile --cpp_out=$1/src/cpp_proto --experimental_allow_proto3_optional
cp $1/src/cpp_proto/*.h $1/message_include
echo "create proto files"
