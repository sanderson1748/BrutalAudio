////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Launch_Button.cpp
//

#include "Launch_Button.h"

#include "../Audio/Audio_Window.h"
#include "../Image/Image_Window.h"

// Launch_Listener ---------------------------------------------------------- //
// Boy is going to come in as Launch_Button
void Launch_Listener::buttonClicked(juce::Button* butt)
{
	Launch_Button* tmp = (Launch_Button*) butt;

	if (tmp->Get_Id() == 1)
	{
		if (tmp->fella == nullptr)	tmp->fella = new Audio_Window("aud");
	}
	else if (tmp->Get_Id() == 2)	
	{
		if (tmp->fella == nullptr)	tmp->fella = new Image_Window("img");
	}
	else	
	{
		std::cout << "negative" << std::endl;	
	}
}

void Launch_Listener::buttonStateChanged(juce::Button* butt)
{
}

// Launch_Button ------------------------------------------------------------ //
Launch_Button::Launch_Button(const char* str, juce::DocumentWindow* in_fella) : juce::TextButton(str)
{
	fella = in_fella;
}

void Launch_Button::Set_Id(int in_id)
{
	id = in_id;
}

int Launch_Button::Get_Id()
{
	return id;
}

//
