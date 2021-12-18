## Overview

This manual gives a basic info about Phobia Motor Controller (PMC). Look into
other docs for specific issues.

## Hardware

We do not assemble hardware for sales. You can get fabrication files from our
[releases](https://sourceforge.net/projects/phobia/files/) or look into repo.

	# hg clone https://hg.code.sf.net/p/phobia/pcb phobia-pcb

You will have to order the fabrication and assembly yourself. You can also try
to contact the [authors](Authors.md) to get samples.

The aim of our PCB design is to optimize electrical and thermal performance.
We are not trying to cram all the components into a small volume. However, we
sometimes cross the border of quality in favor of PCB size.

Our recent hw revision is **REV5A** designed in 8-layer stackup with 35um
copper foil. To ensure heat distribution it is necessary to press an aluminum
plate from bottom through thermal interface.

## Basic wiring

Plug PMC according to the diagram. If you need to run bootloader (in case of
erased MCU) then short BOOT pin to +3.3v before the powerup.

	 +-----------+
	 |           |               +---------------+
	 |  Host PC  |-------//------| USART adapter |
	 |           |               |               |
	 +-----------+               |  GND  RX  TX  |
	                             +---+---+---+---+
	                                 |   |   |
	                                 |   |   |
	                 +---------------+---+---+------+
	 +---------+     |              GND  TX  RX     |           -----
	 |         |-----|                              |----------/     \
	 | Battery |     |    Phobia Motor Controller   |---------|   o   |
	 |         |-----|                              |----------\     /
	 +---------+     |       BOOT  +3.3v            |           -----
	                 +--------+------+--------------+
	                          |      |
	                          +--/ --+

## Software

There are two parts of software:

* Numerical model of VSI with PMSM connected (/sim).
* Firmware for MCU (/src).

The numerical model enables us to develop control code in fast cycle without
hardware tests. It is complete enough to take into account all of motor
parameters. We also provide some set of automated tests which uses a numerical
model. But keep in mind that only abstract control code (/src/phobia) is
covered by these tests.

The firmware can be compiled with appropriate [GCC](https://gcc.gnu.org/)
or [Clang](https://clang.llvm.org/) toolchain for Cortex-M4F target.

	# hg clone https://hg.code.sf.net/p/phobia/code phobia
	# cd phobia/src
	# make flash

We use [stm32flash](https://sourceforge.net/projects/stm32flash/) to upload the
firmware into MCU. You should have a serial port connected to the board TX and
RX pins and BOOT pin shorted to the +3.3v.

You also can upload the firmware through SWD using
[GDB](https://www.gnu.org/software/gdb/). We use
[Black Magic Probe](https://1bitsquared.com/products/black-magic-probe). Be
careful when using hardware debugging while the motor is running. The stop of
feedback loop can cause overcurrent accident.

After the firmware is loaded and ran the command line interface (CLI) will be
available through the same USART. We use
[picocom](https://github.com/npat-efault/picocom) terminal program. Default
baudrate is 57600 with 8-bits data 1-bit even parity and 1-bit stop.

	# make connect

Read the following documentation for setting up.

## User documentation

[Command Line Interface](CLI.md)  
[Input Analog](InputAnalog.md)  
[Input Pulse Width](InputPulseWidth.md)  
[Motor Identification](MotorIdentification.md)  
[Motor Tuning](MotorTuning.md)  
[Network CAN](NetworkCAN.md)  
[Self Test](SelfTest.md)  
[Trouble Shooting](TroubleShooting.md)  

## Developer documentation

[High Frequency Injection](HFI.md)  
[Internals](Internals.md)  
[State Observer](StateObserver.md)  

