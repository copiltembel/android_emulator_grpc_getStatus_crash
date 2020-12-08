# Simple test to demo crashing the android emulator via the GRPC call getStatus()
grpc call getStatus(...) call causes android emulator to crash. This is a simple program to demonstrate this.

Tested with Android emulator version 30.3.4.0

# Build
`$ make`

# Run

First start the emulator with grpc server enabled (ex. `emulator -verbose @Pixel_2 -grpc 8878`)

then run

`$ crashEmu localhost:8878`

# Results

Emulator crashes with seg fault:
```
...
emulator: INFO: GrpcServices.cpp:288: Started GRPC server at 0.0.0.0:8878, security: Insecure
emulator: INFO: boot completed
emulator: INFO: boot time 17145 ms
emulator: Increasing screen off timeout, logcat buffer size to 2M.
emulator: Revoking microphone permissions for Google App.
Segmentation fault (core dumped)
```
