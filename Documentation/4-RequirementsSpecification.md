# 4.0 WaveX - Requirements Specification (Agile User Stories)

## Introduction
WaveX is a software synthesizer in the VST format (Virtual Studio Technology) designed for music producers and sound designers. WaveX includes a variety of sound design tools to assist with music production.

## Epic 1
As a music producer, I want a variety of sound design tools in a VST so that I can create a diverse range of sounds

### Child 1
As a music producer, I want two oscillators with options for sine, square, and saw waveforms, so that I have diverse sound generation capabilities.
#### Acceptance Criteria
  - Verify that two oscillator sections are present in the GUI
  - Verify that each oscillator has a drop-down box allowing it to independently generate sine, square, or saw waveforms
  - Verify that changing the waveform type for one oscillator does not affect the waveform of another oscillator
  - Verify that each oscillator has a knob to control its volume, ranging from 0-100%
  - Verify that that adjusting the volume of one oscillator does not affect volume of the other
  - Verify that each oscillator has a button to turn it on or off, with an LED to indicate if its active
  - Verify that the oscillators are the first step in the signal chain, and are mixed together before being processed by the ADSR

### Child 2
As a music producer, I want an ADSR envelope, so that I can shape the dynamics of my sounds.
#### Acceptance Criteria
- Verify that an ADSR section is present in the GUI
- Verify that the ADSR section has 4 sliders controlling attack, decay, sustain, and release of the output sound, ranging from 0-1000ms
- Verify that each slider is labelled, and updates in real-time as the value is changed
- Verify that the ADSR is applied after both oscillators in the signal chain, and before the filter, reverb and delay.

### Child 3
As a music producer, I want a state variable filter, so that I can shape the tone of my sounds.
#### Acceptance Criteria
- Verify that a filter section is present in the GUI
- Verify that the filter has a drop-down box to switch the filter type between high-pass, band-pass, low-pass
- Verify that the filter has frequency knob, setting the cutoff frequency of the output, ranging from 20-20,000hz
- Verify that the filter has a resonance knob, setting the resonance of the filter shape, ranging from 0.1-10
- Verify that the filter has a button to turn it on or off, with an LED to indicate if its active
- Verift that the filter is applied after the ADSR in the signal chain

### Child 4
As a music producer, I want an LFO, so that I can add movement and modulation to my sounds
#### Acceptance Criteria
- Verify that an LFO section is present in the GUI
- Verify that any user adjustable parameter within the GUI can be mapped to the LFO
- Verify that the LFO has controls to set its speed, ranging from 0-1000ms
- Verify that the LFO has a drop-down box to set its shape as sine, square, or saw
- Verify that the LFO correctly affects the modulated parameter it is mapped to
- Verify that the LFO has a button to turn it on or off, with an LED to indicate if its active

### Child 5
As a music producer, I want chamber reverb and delay effects, so that I can add space and depth to my sounds
#### Acceptance Criteria
- Verify that a Reverb and Delay section are present in the GUI
- Verify that both sections have a button to individually turn on or off, with an LED to indicate if its active
- Verify that both sections have mix controls to set how much of the output is affected by the effect, ranging from 0-100%
- Verify that the reverb has a control to set the room size, ranging from 0-100
- Verify that the delay has a control to set the rate of delay, ranging from 1-1000ms
- Verify that the delay has a control to set the feedback of the delay, rangin from 0-100%
- Verify that the delay is applied after the filter in the signal chain
- Verify that the reverb is applied after the delay in the signal chain

## Epic 2
As a music producer, I want a variety of workflow tools in a VST, so that I can save time and work more efficiently

### Child 1
As a music producer, I want the ability to save and browse presets, so that I can quickly access my favorite sounds
#### Acceptance Criteria
- Verify that a button to access a preset browser section is present in the GUI
- Verify that a save button is present which saves the current state of the VST parameters to a text file
- Verify that opening the preset browser section displays a pop up window over the GUI, showing a list of selectable presets
- Verify that saved presets can be found in the preset browser section
- Verify that when the preset browser display is active, there is a button to close out of it and return to the normal GUI
- Verify that recalling a preset accurately sets the parameters of the VST to the state of the saved preset

### Child 2
As a music producer, I want a waveform visualizer, so that I can get visual feedback on my sound
#### Acceptance Criteria
- Verify that a waveform visualizer is present in the GUI
- Verify that the waveform visualizer is active when a note is played
- Verify that changes to the VST parameters accurately reflect in the output of the waveform visualizer

### Child 3
As a music producer, I want an organized and clean GUI, so that it’s easy to locate parameters
#### Acceptance Criteria
- Verify that each section and control of the VST is accessible from one screen
- Verify that the GUI displays the current value of each control in real-time as it is adjusted
- Verify that the parameter values and names for each control are labelled, accurate, and readable

## Epic 3
As a music producer, I want optimized performance, so that the VST will operate smoothly on my computer

### Child 1
As a music producer, I want low latency, so that my VST runs smoothly
#### Acceptance Criteria
- Verify that real-time processing during playback has low latency within a few milliseconds
### Child 2
As a music producer, I want to quickly load presets, so that my workflow is fluid
#### Acceptance Criteria
- Verify that recalling a saved preset takes under 1 second
### Child 3
As a music producer, I want low CPU usage, so that it runs smoothly on my computer
#### Acceptance Criteria
- Verify CPU usage stays under 10% on a typical use case
### Child 4
As a music producer, I want seamless integration with my Digital Audio Workstation, so that I can send MIDI notes to my VST
#### Acceptance Criteria
- Verify that the VST's specified functionality described above is consistent in both FL Studio and Ableton Live
- Verify that the VST's specified functionality described above is consistent on MacOS
- Verify that the VST correctly detects and responds to MIDI note-on and note-off messages received from the DAW
- Verify that MIDI notes trigger the corresponding sounds within the plugin according to the configured parameters and settings
- Verify that the VST can handle up to 8 voices of polyphony
- Verify that the VST is tuned to 440hz

## Environment Requirements
WaveX can be run as a standalone application on MacOS, or alternatively within a supported DAW

| Hardware Requirements  | Software Requirements      |
| ---------------------- | -------------------------- |
| Intel Core i5 / Apple M1 processor minimum     | MacOS 10.15 or later       |
| 8gb of ram minimum    | FL Studio 21 (optional)    |
|                        | Ableton Live 11 (optional) |

