# PolyFm
My First VST written in C++ using the Juce Framework. 5-Voice Polyphonic FM Synthesizer

# Downloading
https://www.dropbox.com/sh/qswjzlqjt3jh8sl/AACIqkZJ5sEmEjhSwm8ooSzCa?dl=0

The dropbox link above will bring you to a folder containing PolyFM.a, .component, .vst3 and .app files. The .app standalone application currently only works on MacOS. Installation process for the other files is similar to any other standard plugin (ex: C:\Program Files\Common Files\VST3 (windows) Library/Audio/Plug-ins/VST3 (mac))
Once the plugin is in the correct folder, upon trying to load in a DAW you should be prompted to trust the developer, after accepting this, the plugin should load and run in a DAW of your choice.

Alternatively, I have included all source files and the Projucer project. If familiar with Projucer, the project can be opened and compiled with the desired release targets to generate the version of the plug-in that you are interested in installing. 

# Oscillator
The oscillator section includes a drop-down menu to switch between Sine, Saw and Square waves. The oscillator also includes an FM Frequency and FM Depth dial. The frequency modulation wave currently is fixed as a Sine. The FM Depth is in terms of frequency (Depth = 100 results in frequency modulation of +/- 100hz)

# Envelope
The envelope section is a basic four part linear ADSR. Attack, Decay, Sustain and Release dials adjust these paramaters (in Seconds)

# Filter
The filter contains a drop-down menu to switch between low-pass, high-pass and band-pass filters (Known Bug: Filter defaults to low-pass but menu does not display any text). Filter Frequency is adjustable from 20Hz-20kHz. Filter resonance is adjustable from 0-10. 

# Gain
An overall gain (0...1) is provided at the right hand side of the screen

# Background/Future Development
This synth is my first attempt at coding a VST synth. It's initial form seen here is a relatively basic FM synthesizer. I used a combination of information from tutorials on https://juce.com/learn/tutorials. Videos by https://www.youtube.com/c/TheAudioProgrammer and https://www.youtube.com/channel/UCwEc_CsAk3ky7sX_yg6bSSg were also highly useful during this learning process. 

I plan on continuing the development of this VST. Some of my current goals include: Adjusting the value skews on various dials (specifically filter frequency) to allow for more fine controll in the lower ranges, Adding an LFO and a second envelope for the filter, adding a variety of presets. As more of a long-term goal, I plan to add microtonal capabilities to the plugin, allowing for custom scales and custom midi mapping. 
