*** Settings ***
Suite Setup                         Setup
Suite Teardown                      Teardown
Test Teardown                       Test Teardown
Resource                            ${RENODEKEYWORDS}

*** Variables ***
${SCRIPT}                           ${CURDIR}/stm32f4-disco-test.resc
${UART}                             sysbus.usart2

*** Keywords ***
Start Firmware
    Execute Script                  ${SCRIPT}
    Create Terminal Tester          ${UART}    timeout=3    defaultPauseEmulation=True
    Execute Command                 emulation SetGlobalSerialExecution true
    Start Emulation

*** Test Cases ***
Should Report Successful SelfTest
    Start Firmware
    Wait For Line On Uart           BOOT:START
    Wait For Line On Uart           SELFTEST:PASS checksum=86931263

Should Toggle HeartbeatLedState
    Start Firmware
    Wait For Line On Uart           BOOT:START
    Wait For Line On Uart           SELFTEST:PASS checksum=86931263
    Wait For Line On Uart           HEARTBEAT:1 led=1
    Wait For Line On Uart           HEARTBEAT:2 led=0
    Wait For Line On Uart           HEARTBEAT:3 led=1