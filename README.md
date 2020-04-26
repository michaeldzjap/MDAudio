# MDAudio
A(nother) C++ audio signal processing library

## Requirements

- C++17
- [CMake](https://cmake.org/)

## Available Generators and Processors

- Wavetable Oscillators
    - SineOscillator
    - HannOscillator (Raised-Cosine)

- Delays (Basic)
    - DelayStatic
    - DelayLinear
    - DelayCubic
    - TapDelayStatic
    - TapDelayLinear
    - TapDelayCubic
    - AllpassStatic
    - AllpassLinear
    - AllpassCubic

- Delay Based Effects
    - ReverseDelay
    - ReversibleDelay
    - PitchShifter

- TPT Filters
    - LowpassFirstOrder
    - LowpassSecondOrder
    - HighpassFirstOrder
    - HighpassSecondOrder
    - LowshelfFirstOrder
    - LowshelfSecondOrder
    - HighshelfFirstOrder
    - HighshelfSecondOrder
    - Bandshelf
    - Bandpass
    - Bandstop
    - AllpassFirstOrder
    - AllpassSecondOrder
