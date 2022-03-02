## Introduction
Rtkaller is a task state awaresd fuzzer for RTOS fuzzing, It generates high quality tasks to fully test the entire RTOS and can test for various types of vulnerabilities within the RTOS.

The process structure for the Rtkaller system is shown in the following diagram; 

![Process structure for Rtkaller](./design.png?raw=true) 

## Task Schema
The `Task Schema` is a data structrue within Rtkaller, we modified the test case [generation](../prog/generation.go) and the [mutation](../prog/mutation.go) module in Syzkaller, enhanced it to generate Task, instead of single program. 
In detail, the Task contains a set of SPEC(syscall descriptions) and a concurrency intensity, in which the SPEC is based on Syzkaller, and the intensity indicate how many test cases Rtkaller will execute concurrently.
To write new SPEC for RTOS fuzzing, RTOS related domain kownledeges are required. 

To further improve the fuzzing effectiveness, we implenmented a task repair machenism also in [generation](../prog/generation.go) module, which allows Rtkaller to automaticlly detect and repair those abnormal test cases.  

## Parallelized Task Execution
For `task execution`, to cover more real time related code and improve fuzzing efficiency, we devise a parallelized task execution method in fuzzer module, its code can be seen at [1](../pkg/ipc/ipc.go), [2](syz-fuzzer/fuzzer.go), [3](syz-fuzzer/proc.go) and other files located in pkg/syz-fuzzer modules. This modifications enabled Rtkaller to  multiple execution concurrently and asynchronouly collect the runtime information.  

## Coverage

Rtkaller is a coverage-guided fuzzer. We first uses python script for real time code extrction and targeting instrumentation and modified Syzkaller for real time code collection, the detailed implementation can be seen at [1](../executor/common.h), [2](../syz-manager/manager.go), [3](../pkg/cover/cover.go), [4](../syz-fuzzer/proc.go) and other modules at pkg and syz-fuzzer modules.
