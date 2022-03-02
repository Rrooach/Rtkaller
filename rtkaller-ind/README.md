### Introduction
Here we provide a binary executor for newly adapted traditional RTOSes fuzzing.
The executor is ported from Rtkaller, currently supporting [Erika](https://github.com/evidence/erika3) fuzzing.
<!-- [FreeRTOS](https://github.com/FreeRTOS/FreeRTOS) and -->
The code diectory is constructed as follow:
In src directory we provide necessary executor code, and in bin directory we provide 
- Binary executor __fuzzer__ 
- Seeds generator __gen__<!-- - FreeRTOS image __RTOS.bin__ -->
- Erika image __erika.bin__

<!-- For bug detection, see [buglist](../docs/buglist.md) in detail. -->

### Run
`rtkaller-ind` requires essentially no configuration, however it do needs an extra LICENSE for t32 emulator. Run ```./bin/fuzzer --help ``` to see different options.

