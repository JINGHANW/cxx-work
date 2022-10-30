//
// Created by wjh on 22-10-16.
//

#include<iostream>
#include<grpcpp/grpcpp.h>
#include<string>
#include<memory>
#include"helloworld.grpc.pb.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloRequest;
using helloworld::HelloReply;

class GreeterClient{
public:
    GreeterClient(std::shared_ptr<Channel> channel)
            : stub_(Greeter::NewStub(channel)) {}
    std::string SayHello(const std::string& user){
        HelloRequest request;
        request.set_name(user);
        HelloReply reply;
        ClientContext context;
        Status status;
        status=stub_->SayHello(&context,request,&reply);
        if(status.ok()){
            return reply.message();
        }else{
            std::cout<<status.error_code()<<":"<<status.error_message()<<std::endl;
            return "RPC FAILED";
        }
    }

    std::string SayHelloAgain(const std::string& user){
        HelloRequest request;
        request.set_name(user);
        HelloReply reply;
        ClientContext context;
        Status status;
        status=stub_->SayHello(&context,request,&reply);
        if(status.ok()){
            return reply.message();
        }else{
            std::cout<<status.error_code()<<":"<<status.error_message()<<std::endl;
            return "RPC FAILED";
        }
    }

private:
    std::shared_ptr<Greeter::Stub> stub_;
};
int main(int argc, char** argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint specified by
    // the argument "--target=" which is the only expected argument.
    // We indicate that the channel isn't authenticated (use of
    // InsecureChannelCredentials()).
    std::string target_str;
    std::string arg_str("--target");
    if (argc > 1) {
        std::string arg_val = argv[1];
        size_t start_pos = arg_val.find(arg_str);
        if (start_pos != std::string::npos) {
            start_pos += arg_str.size();
            if (arg_val[start_pos] == '=') {
                target_str = arg_val.substr(start_pos + 1);
            } else {
                std::cout << "The only correct argument syntax is --target=" << std::endl;
                return 0;
            }
        } else {
            std::cout << "The only acceptable argument is --target=" << std::endl;
            return 0;
        }
    } else {
        target_str = "127.0.0.1:50000";
    }
    std::cout<<"target_str"<<target_str<<std::endl;
    GreeterClient greeter(grpc::CreateChannel(
            target_str, grpc::InsecureChannelCredentials()));
    std::string user("world");

    while (1){
        std::string reply = greeter.SayHello(user);
        std::cout << "Greeter received: " << reply << std::endl;

        reply = greeter.SayHelloAgain(user);
        std::cout << "Greeter received: " << reply << std::endl;
    }

    return 0;
}
