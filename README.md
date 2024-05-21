# KR260 Hardware platfrom with Zynq MPSoC UART and GPIO

The following project is an example design of how to create a PL UART And GPIO
and control the interfaces via Software. This project uses freeRTOS to 
run tasks simultaneously at different schedules.

The project has three sections. Section 1 is meant to blink an led with two separate tasks,
each lighting up the led at different intervals. Section 2 utulizes an RTOS queue to print lines. 
Section 3 prints four different messages each with a separate task and unique 
priorities to give them different rates.


Use the provided Firmware to create FreeRTOS examples on the PS side.

To build the Firmware run the followings from the hardware folder:

```shell
cd hardware
source ./synth.tcl
create_target
```
*Section 1 and 2 code was provided by the instructor, section 3 was completed by me.
The goal of this project was to learn how to create xsa files using a block design
and using that xsa platform to run freeRTOS tasks through Vitis. I also
learned how to create applications in Xilinx Vitis.*
