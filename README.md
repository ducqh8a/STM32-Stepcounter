# EMBEDDED UET - STEP COUNTER

## Contributors
* Nguyễn Khắc Kiên - 20020679 - K65K
* Hồ Sỹ Trung Đức - 20020648 - K65K

## Introduction
Bài tập lớn cuối kỳ - Step Counter using MPU6050 with STM32F103C8T6 (Môn học: Nhập Môn Hệ Thống Nhúng - ELT3240 1)

## Systems and Engine

- Build with Keil C
- Using Standard Library
- Using STM32F103C8T6
- Using MPU6050
- Using LCD16x2
- Using USB to TTL ( BOOT LOADER )
- Using 2 Switch ( SS and Reset )
- Using Red LED and Blue LED

## Features

### I2C Interface

- Using I2C interface to print Data to LCD16x2 and Read Data from MPU6050

### TIMER2 and Systick Timer

- Using TIM2 to blink Blue LED 
- Using Systich Timer create function delay microsecond

### GPIO Input and Output

- Using 2 Input Switch ( SS and Reset ) to start/stop and reset system
- Using Red LED and Blue LED to show current status

### Algorithm to compare vectors in space

- Using algorithm to compare vectors in space to calculate Step Counter
