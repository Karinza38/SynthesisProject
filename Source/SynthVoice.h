/*
  ==============================================================================

    SynthVoice.h
    Created: 28 Oct 2020 4:13:30pm
    Author:  chold

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"



class SynthVoice: public juce::SynthesiserVoice {

public: 
    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity,
        juce::SynthesiserSound* sound, int currentPitchWheelPosition);

    void stopNote(float velocity, bool allowTailOff);


    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outPutChannels);

    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, 
        int startSample, int numSamples) override;
    

private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    juce::AudioBuffer<float> synthBuffer;

    juce::dsp::StateVariableTPTFilter<float> filter;


    bool isPrepared{ false };

    juce::dsp::Oscillator<float> sawOsc { [](float x) { return x / juce::MathConstants<float>::pi; } };
    juce::dsp::Oscillator<float> squareOsc{ [](float x) { return x < 0.0f ? -1.0f : 1.0f; }, 100 };

    // return std::sin (x); //Sine Wave
    // return x / MathConstants<float>::pi; // Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f;  // Square Wave


    juce::dsp::Gain<float> gain;

};