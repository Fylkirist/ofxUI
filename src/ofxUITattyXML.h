#pragma once
#include "ofMain.h"

class ofxUISuperCanvas;
class ofxUITattyXML
{
public:
	virtual void saveSettings(string fileName);
    virtual void loadSettings(string fileName);

private:
	vector<ofxUISuperCanvas> canvas;
};