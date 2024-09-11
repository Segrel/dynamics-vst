# Dynamics - a compressor plugin with ML ✨

Real-time audio plugin based on the concepts and work of "[Grey-Box Modelling of Dynamic Range Compression](http://research.spa.aalto.fi/publications/papers/dafx22-DDRC/)" by Alec Wright and Vesa Välimäki. The plugin implementation allows for manual adjustment of threshold, ratio and knee width for the compressor, or use an ML based approximation of an LA-2A Leveling Amplifier compressor's Peak Reduction adjustment. Additionally, a Warmth component can be added to emulate an analog system response.

## Pre-requisites

**MacOS**:
 - [XCode](https://developer.apple.com/xcode/) 
 - [Developer Command Line Tools](https://www.youtube.com/watch?v=sF9UszljnZU)
 - [CMake](https://cmake.org/) - Can also be installed with [Homebrew](https://formulae.brew.sh/formula/cmake)

**Windows**:
 - [MS Visual Studio](https://visualstudio.microsoft.com/vs/community/) (2019/2022) - Community Edition is free.
 - [Git Bash](https://gitforwindows.org/)
 - [CMake](https://cmake.org/)

**Linux**:
 - [Linux JUCE dep.](https://github.com/juce-framework/JUCE/blob/master/docs/Linux%20Dependencies.md)

## Cloning the Repository
If you have a [github account](https://docs.github.com/en/get-started/signing-up-for-github/signing-up-for-a-new-github-account) with a [SSH key setup](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account):
```
git clone --recurse-submodules git@github.com:joaorossi/modern-real-time-audio.git
```
Otherwise, the `https` will also work.
```
git clone --recurse-submodules https://github.com/joaorossi/modern-real-time-audio.git
```

## Build the project
```
./configure.sh
./build.sh dynamics
```
