//
// Created by wjh on 22-10-16.
//
#include<iostream>
#include<string>
#include<memory>
#include<grpcpp/grpcpp.h>
#include<grpcpp/ext/proto_server_reflection_plugin.h>
#include<grpcpp/health_check_service_interface.h>
#include"helloworld.grpc.pb.h"
using grpc::Server;
using grpc::Service;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerBuilder;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;
class GreeteServiceImpl final :public Greeter::Service{
    Status SayHello(ServerContext *context,const HelloRequest * request,HelloReply*reply) override{
        std::string prefix("Hello");
        reply->set_message(prefix+request->name());
        return Status::OK;
    }
    Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
                         HelloReply* reply) override {
        std::string prefix("Hello again ");
        reply->set_message(prefix + request->name());
        return Status::OK;
    }
};

void RunServer(){
    std::string server_address("127.0.0.1:50000");
    GreeteServiceImpl greeteService;
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder serverBuilder;
    serverBuilder.AddListeningPort(server_address,grpc::InsecureServerCredentials());
    serverBuilder.RegisterService(&greeteService);
    std::unique_ptr<Server> server(serverBuilder.BuildAndStart());
    std::cout<<"Build And Start"<<server_address<<std::endl;
    server->Wait();
}
int main(){
    RunServer();
    return 0;
}