# WaveX - Software Development Plan

## 4.1   Plan Introduction
This Software Development Plan details the planned development for the WaveX softare synthesizer, which provides users with the ability to design sounds for use in audio production.

WaveX will feature a variety of sound design tools including 2 oscillators, an ADSR envelope, a filter, reverb and delay effects. These tools will allow a user to
shape the sound to their liking. Additionally, since WaveX will be made in the VST format, it can be used within DAW's to sequence MIDI notes 
WaveX will be made in the VST format, meaning MIDI compatability 


## 4.1.1 Project Deliverables
- Written Status Report (Every other Monday starting Week 8)
    - Status reports will cover current progress on the project.
    - Accomplishments, scheduled tasks for the next two weeks, and risks / problems will be included as sections
- Updated Software Development Plan (Week 12)
    - The software development plan will be updated and revised to match the current status of the project.
    - There may be changes to the project timeline and schedule which should be documented to ensure the project will be completed on time.
- Updated Requirements Specification (Week 13)
    - The requirements specification will be updated and filled out to match any new additions or removals from the project.
- Preliminary Demonstration (Week 13/14)
    - An MVP of WaveX will be prepared for demonstration, showcasing its features and capabilities.
    - By this point WaveX should have minimal functionality completed, including 2 oscillators, ADSR envelope, a filter, a preset browser, and a GUI
- Preliminary Poster (Week 14)
    - A visually appealing poster will be created to highlight WaveX's features.
- Final Product (Week 16)
    - The final version of WaveX will be completed with any additional stretch goals implemented since the preliminary demonstration
    - The project will be presented, along with a finalized poster.

## 4.2   Project Resources
This section provides resource information for the WaveX project

## 4.2.1 Hardware Resources
The project will be developed on a 2019 i9 8-core MacBook Pro with 32GB of ram.
It will also be tested on a 2021 M1 Max MacBook Pro with 64GB of ram.
A Native Instruments A49 MIDI controller will be used as well to test MIDI functionality of the project, however is not required to use the software.
WaveX will only be tested on the development laptop running MacOS, as such it will only officially support the MacOS operating system.
The execution of the final project will only require a modern computer running MacOS.

## 4.2.2 Software Resources
The software / OS planned to be used for this development is listed below
- MacOS Catalina 10.15.7
- MacOS Monterey 12.5.1
- Xcode 12.4
- JUCE framework 7.0.10
- Ableton Live 11
- FL Studio 21

## 4.3   Project Organization
The major functions of the project are divided as follows
- Sound Design
    - This will be the bulk of the project and the first section to be completed
    - It will include implementing all the sound design features of the synth
        - 2 oscillators
        - ADSR envelope
        - filter
        - reverb and delay
        - waveform visualizer
- Preset Browser
    - The preset browser will be completed next, it will allow the users to save and reload patches for the synth
- GUI
    - A basic skeleton for the GUI will be developed alongside the prior sections, however it will be fully polished and finalized once the other parts are completed
- Stretch Goals
  - If progress is faster than expected, this feature will be added to the sound design section of the synth. The GUI will have to be adjusted as well to incorporate this section
    - LFO


## 4.4   Project Schedule
This section provides schedule information for the WaveX project

## 4.4.1 GANTT Chart
![GANTT CHART](https://github.com/georgeh02/seniorproject2/blob/main/Deliverables/GANTT_V1.png)

## 4.4.2 Task / Resource Table
All tasks will be handled by one person, using all resources mentioned in section 4.2
