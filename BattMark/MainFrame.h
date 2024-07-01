#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnTimer(wxTimerEvent& evt);
	void OnSize(wxSizeEvent& evt);
	void UpdateSizes(wxSize windowSize);
	UINT8 GetPercentage();
	char* GetTime();
	wxGauge* batteryBar;
	wxStaticText* batteryPercentage;
	wxTimer* timer;
	wxPanel* panel;
	wxStaticText* timeText;
	wxSize timeTextSize;
	wxFont timeTextFont;
	const int buttonMargin=100;
	const int buttonDownDistance=40;
};

