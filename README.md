<img src="Deliverables/images/logo1.png">

# [WaveX](https://github.com/georgeh02/seniorproject2)
Created by George Harrison

WaveX is a simple monophonic synthesizer created using the JUCE framework.

It features a variety of components that make sound design easy for music producers.

<div align="center">
<img src="Deliverables/images/WaveX.png" width="500">
</div>

## WaveX Features
- 2 oscillators with gain controls and 3 different wave types (Sine, Saw, Square)
- ADSR module to control attack, decay, sustain, release
- Filter module with 3 different types (Low Pass, Band Pass, High Pass)
- Delay module with time, feedback, and mix controls
- Reverb module with room size and mix controls
- Waveform visualizer
- A clean and organized GUI with a playable keyboard
- Safety limiter to ensure volume does not go over 0 db
- Compatible with MacOS (Standalone, VST3, AU formats)

## Installation Instructions
### Standalone
- WaveX can be easily run in standalone mode by running [WaveX.app](https://github.com/georgeh02/seniorproject2/blob/main/WaveX%20Builds/WaveX.app.zip)
- Preview the sounds you create by using the GUI keyboard

### Within a DAW
- WaveX can be used within most DAWs as a third party plugin
- To use WaveX within your DAW, download your preferred plugin format
    - For VST3, copy [WaveX.vst3](https://github.com/georgeh02/seniorproject2/blob/main/WaveX%20Builds/WaveX.vst3.zip) to "/Library/Audio/Plug-Ins/VST3"
    - For AU, copy [WaveX.component](https://github.com/georgeh02/seniorproject2/blob/main/WaveX%20Builds/WaveX.component.zip) to "/Library/Audio/Plug-Ins/Components"
- Once your preferred version is installed, simply rescan your DAW and WaveX will be ready to use
