#include <grpcpp/client_context.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "grpc_bindings/emulator_controller.grpc.pb.h"
#include "grpc_bindings/emulator_controller.pb.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using grpc::Channel;
using namespace android::emulation::control;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: ./crashemu grpcServerAddress:port");
        return -1;
    }

    auto channel = grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials());
    auto emuController = EmulatorController::NewStub(channel);

    int errors = 0;
    uint64_t uptime = 0;
    bool booted = false;

    do {
        sleep(1);
        try {
            grpc::ClientContext context;
            context.set_wait_for_ready(true);
            google::protobuf::Empty empty;
            EmulatorStatus response;
            emuController->getStatus(&context, empty, &response);
            booted = response.booted(); // emu crashes when calling this
            uptime = response.uptime();
        } catch (int n) {
            errors++;
        }
    } while (!booted && uptime < 1000 && errors < 30);

    if (!booted) {
        return -2;
    }

    return 0;
}
