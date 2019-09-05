server:main.cpp structHeader.cpp Protocal.pb.cc Protocal.pb.h chat_message.h structHeader.h JsonObject.h
	g++ -O2 -g -std=c++14 -o server main.cpp structHeader.cpp Protocal.pb.cc -lboost_system -lboost_serialization -lpthread -lprotobuf
client:client.cpp structHeader.cpp Protocal.pb.cc Protocal.pb.h chat_message.h structHeader.h JsonObject.h
	g++ -O2 -g -std=c++14 -o client client.cpp structHeader.cpp Protocal.pb.cc -lboost_system -lboost_serialization -lpthread -lprotobuf
