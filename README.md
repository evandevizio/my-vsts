# my-vsts
A collection of VST effect plugins I made using the JUCE C++ framework. Add these software modules to your DAW for maximum audio mangling and manipulation!

## Summary
This repository contains the dll files and source files for three different VST plugins I developed using JUCE. Their names are "AStateVariableFilter", "ADistortionEffect", and "ABitcrusherEffect". Very self-descriptive! **The included dll files are in VST format for 64-bit Windows systems**. The GUI controls are flexible, allowing both horizontal and vertical mouse movements, and the parameters can be mapped to MIDI devices. To install, move one or more of the dll files to the directory where your DAW scans for VST plugins. In order to build these plugins yourself, you will need the C++ source files, the JUCE library code, and the VST SDK from Steinberg.

**WARNING**: The output from these modules can be *very* loud, and potentially damage your sound equipment and/or eardrums! **Please use caution when adjusting the parameters.**

## AStateVariableFilter

A general-purpose filter effect with cutoff and resonance controls. Perfect for blocking problem frequencies, sweeping audio spectrums, or shaping sounds in real-time.

![Image](https://github.com/evandevizio/my-vsts/blob/master/screenshots/filter.jpg)

  - **Filter Type**: selects the filter shape (low-pass, band-pass, or high-pass) with 12 dB of attenuation / octave.
  
  - **Cutoff**: changes the cutoff frequency of the filter, measured in Hz.
  
  - **Resonance**: amplifies frequencies around the cutoff value.

## ADistortionEffect

A nifty stompbox-style distortion unit that adds a range of character to your sound, from subtle and crunchy to over-the-top aggressive. Features a visualizer that dynamically displays the processed audio waveform.

![Image](https://github.com/evandevizio/my-vsts/blob/master/screenshots/distort.jpg)

  - **Drive**: adjusts the amount of dirt applied to the incoming audio.
  
  - **Depth**: changes the distortion threshold, used in conjunction with the **Drive** knob. 
  
  - **Mix**: blends both the raw signal and processed signal.
  
  - **Volume**: boosts the output volume of the processed signal.

## ABitcrusherEffect

A classic lo-fi module that reduces the bit depth and sampling rate of anything you throw at it. Great for achieving grainy, retro-like sounds.

![Image](https://github.com/evandevizio/my-vsts/blob/master/screenshots/bit.jpg)

  - **Noise**: sets the amount of white noise to add to the signal.
  
  - **Bits**: reduces the bit depth of the incoming audio.
  
  - **Rate Reduction**: reduces the sampling rate of the incoming audio.
  
  ## Credits
  
  Developed by [Evan DeVizio](https://evandevizio.com)
  
  Special thanks to: 
  
  [Joshua Hodge](https://theaudioprogrammer.com/) (The Audio Programmer Ltd), [Aaron Leese](https://www.stagecraftsoftware.com/about/) (Stagecraft Software), and [Reon Fourie](https://www.youtube.com/channel/UCFNHiD7cM4l3Mwfs3ENjJyw) for their informative videos and plentiful knowledge!
  
  The [JUCE](https://juce.com/) team, [Steinberg](https://www.steinberg.net/en/home.html), and the [Renoise](https://www.renoise.com/) team for their amazing software!
  
  **Thank you!**
