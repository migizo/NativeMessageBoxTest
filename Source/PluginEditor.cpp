/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NativeMessageBoxTestAudioProcessorEditor::NativeMessageBoxTestAudioProcessorEditor (NativeMessageBoxTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), openDialogButtons(buttonTexts.size())
{
    int h = 30;
    int offset = 10;
    
    iconTypeComboBox.reset(new ComboBox);
    addAndMakeVisible(iconTypeComboBox.get());
    iconTypeComboBox->setBounds(offset, offset, 200, h);
    iconTypeComboBox->addItem("NoIcon", 1);
    iconTypeComboBox->addItem("QuestionIcon", 2);
    iconTypeComboBox->addItem("WarningIcon", 3);
    iconTypeComboBox->addItem("InfoIcon", 4);
    iconTypeComboBox->setSelectedItemIndex(0);

    for (int i = 0; i < buttonTexts.size(); i++) {
        openDialogButtons[i].reset(new TextButton(buttonTexts[i], buttonTexts[i]));
        addAndMakeVisible(openDialogButtons[i].get());
        openDialogButtons[i]->setBounds(100, offset + (offset + h) * (i + 1), 200, h);
    }
    
    // reference : https://qiita.com/ring2/items/b024084be6cccc9e2601
    for (int i = 0; i < buttonTexts.size(); i++) {
        openDialogButtons[i]->onClick = [i, this]() {
            
            MessageBoxIconType iconType;
            int comboIndex = iconTypeComboBox->getSelectedItemIndex();
            if (comboIndex == 0) iconType = MessageBoxIconType::NoIcon;
            else if (comboIndex == 1) iconType = MessageBoxIconType::QuestionIcon;
            else if (comboIndex == 2) iconType = MessageBoxIconType::WarningIcon;
            else if (comboIndex == 3) iconType = MessageBoxIconType::InfoIcon;

            String title(buttonTexts[i]);
            String msg(TRANS(title + "\n" + "this is message"));
                        
            function<void(int)> callback = [](int result) {
                DBG("result : " << result);
            };
            
            if (buttonTexts[i] == "showAsync") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                                                .withIconType(MessageBoxIconType::InfoIcon)
                                                .withTitle(buttonTexts[i])
                                                .withMessage(msg)
                                                .withButton(TRANS("button")),
                                            callback);
            }
            else if (buttonTexts[i] == "showMessageBoxAsync") {
                NativeMessageBox::showMessageBoxAsync(iconType, title, msg);
            }
            else if (buttonTexts[i] == "showOkCancelBox") {
                NativeMessageBox::showOkCancelBox(iconType, title, msg, nullptr, ModalCallbackFunction::create(callback));
            }
            else if (buttonTexts[i] == "showYesNoCancelBox") {
                NativeMessageBox::showYesNoCancelBox(iconType, title, msg, nullptr, ModalCallbackFunction::create(callback));
            }
            else if (buttonTexts[i] == "showYesNoBox") {
                NativeMessageBox::showYesNoBox(iconType, title, msg, nullptr, ModalCallbackFunction::create(callback));
            }
        };
    }
    
    setSize (400, 300);
}

NativeMessageBoxTestAudioProcessorEditor::~NativeMessageBoxTestAudioProcessorEditor()
{
    for (int i = 0; i < buttonTexts.size(); i++) {
        openDialogButtons[i] = nullptr;
    }
    iconTypeComboBox = nullptr;
}

//==============================================================================
void NativeMessageBoxTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NativeMessageBoxTestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
