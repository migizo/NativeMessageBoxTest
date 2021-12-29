/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
using namespace juce;
using namespace std;
//==============================================================================
/**
*/
class NativeMessageBoxTestAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NativeMessageBoxTestAudioProcessorEditor (NativeMessageBoxTestAudioProcessor&);
    ~NativeMessageBoxTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    unique_ptr<ComboBox> iconTypeComboBox;
    
    vector<string> buttonTexts = {
        "showAsync",
        "showMessageBoxAsync",
        "showOkCancelBox",
        "showYesNoCancelBox",
        "showYesNoBox"
    };
    vector<unique_ptr<TextButton> > openDialogButtons;
        
    NativeMessageBoxTestAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NativeMessageBoxTestAudioProcessorEditor)
};
