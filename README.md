# STM32F4 Discovery Renode Loop

This project builds a small STM32F4 Discovery firmware image and runs it under Renode.

The current firmware path is intentionally minimal for emulation:
- `main()` is limited to HAL startup, clock configuration, and the main loop
- board-specific GPIO/UART glue lives in `Core/Src/board.c`
- application behavior lives in `Core/Src/app.c`
- the firmware emits deterministic UART lines that Renode can assert on
- the USART2 DMA and IRQ path is removed from the Renode-oriented build path to reduce emulator noise

## What the firmware does

On boot it prints:

```text
BOOT:START
SELFTEST:PASS checksum=86931263
```

Then every 500 ms it prints a heartbeat line and toggles the green LED state in software:

```text
HEARTBEAT:1 led=1
HEARTBEAT:2 led=0
```

## Build

From the `stm32f4-disco` folder:

```powershell
cmake --preset Debug
cmake --build build/Debug
```

## Run in Renode

From the workspace root:

```powershell
d:\CURRENT-WORK\duvitech\stm32-unit-tests\renode_1.16.1-portable\renode.exe --plain --disable-gui --console d:\CURRENT-WORK\duvitech\stm32-unit-tests\stm32f4-disco\renode\stm32f4-disco.resc
```

If you want to type the command inside the Renode monitor instead, use:

```text
i @d:\CURRENT-WORK\duvitech\stm32-unit-tests\stm32f4-disco\renode\stm32f4-disco.resc
```

## Run the automated Renode smoke test

From the workspace root:

```powershell
c:\python314\python.exe d:\CURRENT-WORK\duvitech\stm32-unit-tests\renode_1.16.1-portable\tests\run_tests.py --css-file d:\CURRENT-WORK\duvitech\stm32-unit-tests\renode_1.16.1-portable\tests\robot.css --robot-framework-remote-server-full-directory d:\CURRENT-WORK\duvitech\stm32-unit-tests\renode_1.16.1-portable -r d:\CURRENT-WORK\duvitech\stm32-unit-tests d:\CURRENT-WORK\duvitech\stm32-unit-tests\stm32f4-disco\renode\stm32f4-disco.robot
```

The test passes when Renode observes the deterministic UART sequence from the firmware.

The suite currently covers two behaviors:
- boot plus self-test success
- heartbeat LED state toggling across multiple ticks

## Files

- `Core/Src/app.c`: deterministic application logic used by Renode tests
- `Core/Src/board.c`: minimal board GPIO/UART implementation for emulation
- `Core/Inc/app.h`: application state and API
- `Core/Inc/board.h`: board abstraction used by `main.c`
- `renode/stm32f4-disco.resc`: interactive Renode launcher
- `renode/stm32f4-disco-test.resc`: headless script for automation
- `renode/stm32f4-disco.robot`: Robot smoke test