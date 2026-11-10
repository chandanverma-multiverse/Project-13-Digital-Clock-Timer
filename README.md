main.cpp
# Project 13: Digital Clock & Countdown Timer (v2.0)

**Project Group ID:** 13  
**Team Members:**
* **Het** (Roll Number: 21)
* **Chandan** (Roll Number: 20)

## Project Overview
A C++ console application featuring a live Digital Clock and a customizable Countdown Timer built using Object-Oriented Programming (OOP) principles.

## System Architecture (Version 2.0)
* **`DigitalClock`**: Fetches and formats system time continuously in `HH:MM:SS` format.
* **`CountdownTimer`**: Accepts user duration (`Hours`, `Minutes`, `Seconds`), validates inputs, and counts down to `00:00:00` with a `"Time's Up!"` alert.
* **`DigitalClockTimerApp`**: Coordinates the main menu loop, user choices, and error handling.

## How to Compile and Run
```bash
g++ main.cpp -o clock_timer_v2
./clock_timer_v2
