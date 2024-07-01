#include "MainFrame.h"
#include <wx/wx.h>
#include <WinBase.h>
#include <ctime>

MainFrame::MainFrame(const wxString& title):wxFrame(nullptr,wxID_ANY, title) {

	panel = new wxPanel(this);
	int screenY;
	int screenX;
	this->GetSize(&screenX, &screenY);
	wxLogDebug("Size: %d",screenX);
	timeText = new wxStaticText(panel, wxID_ANY, GetTime(), wxPoint(0, 50), wxSize(screenX, 50), wxALIGN_CENTER_HORIZONTAL);

	batteryPercentage = new wxStaticText(panel, wxID_ANY, "0%", wxPoint(screenX-buttonMargin,screenY/2), wxSize(50, 20));
	batteryBar = new wxGauge(panel, wxID_ANY, 100, wxPoint(buttonMargin, screenY / 2), wxSize(screenX - buttonMargin*2, 30));
	timer = new wxTimer(this);

	this->Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
	this->Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
	(*this->timer).Start(1000);
}

void MainFrame::OnTimer(wxTimerEvent& evt) {
	UINT8 percentage = this->GetPercentage();
	batteryPercentage->SetLabel(std::to_string(std::min<int>(percentage,100)) + "%");
	batteryBar->SetValue(percentage);
	timeText->SetLabel(GetTime());
	timeText->SetSize(timeTextSize);
}

char* MainFrame::GetTime() {
	time_t time = std::time(0);
	char* dt = ctime(&time);
	tm* gmtm = gmtime(&time);
	dt = asctime(gmtm);
	return dt;
}

UINT8 MainFrame::GetPercentage() {
	SYSTEM_POWER_STATUS status;
	GetSystemPowerStatus(&status);
	return status.BatteryLifePercent;
}

void MainFrame::UpdateSizes(wxSize windowSize) {
	panel->SetSize(windowSize);
	batteryBar->SetPosition(wxPoint(buttonMargin, windowSize.y-(windowSize.y/8) - buttonMargin));
	batteryBar->SetSize(wxSize((windowSize.x - buttonMargin * 2)-(windowSize.y/20)*3, windowSize.y/8));
	batteryPercentage->SetPosition(wxPoint(windowSize.x - buttonMargin - (windowSize.y / 20) * 3, batteryBar->GetPosition().y));
	wxFont font = batteryPercentage->GetFont(); font.SetPointSize(windowSize.y/20); batteryPercentage->SetFont(font);
	timeTextFont = timeText->GetFont();
	timeTextFont.SetPointSize(std::min(windowSize.y / 22,35));
	timeTextSize = wxSize(windowSize.x, 50);
	timeText->SetSize(timeTextSize);
	timeText->SetFont(timeTextFont);
	
}

void MainFrame::OnSize(wxSizeEvent& evt) {
	UpdateSizes(evt.GetSize());
}

