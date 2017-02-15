#pragma once

#include "ofMain.h"
#include "ofxGifDecoder.h"
#include "ofxGifFile.h"
#include "ofxGui.h"

class eye
{
public:
	enum eye_type { LEFT_EYE, RIGHT_EYE, CUSTOM };
	
	void setup(ofRectangle rect, vector<ofVideoDevice> deviceList, eye_type type);
	void update();
	void draw();
	void exit();

	void drawBackground();
	void recalculateThePositionOfTheFrame();
	ofRectangle getRect() { return mainRect; }

	void setActive(bool activ);
	bool getActive() { return enable; }

	void setNotCut(bool not_cut) { notCut = not_cut; recalculateThePositionOfTheFrame(); }
	bool getNotCut() { return notCut; }

	void setEyeType(eye_type type) { m_eye_type = type; }
	eye_type getEyeType() { return m_eye_type; }

	void setSquint(bool sq) { squint = sq; recalculateThePositionOfTheFrame(); }
	bool getSquint() { return squint; }
	
	void setMargins(int margins);
	int getMargins() { return lateral_margins; }

	void rotateImage(int addAngle);
	int getRotateAngle() { return rotate; }
	
	void changeCam(int index);
	int getIndexCam() { return indexCam; }

	void setShowGui(bool show) { showGui = show; }
	bool getShowGui() { return showGui; }

	void enableToggleChange() { setActive(enableToggle); }
	void changeMarginSlider(int &margin) { setMargins(margin); }
	void rotatePlusClick() { rotateImage(90); }
	void rotateMinusClick() { rotateImage(-90); }
	void camButtonClick();
	void changeNotCut() { setNotCut(notCutToggle); }
	void changeSquint() { setSquint(squintToggle); }
private:
	void camInit();
	void camDelete();

	ofRectangle mainRect, viewRect;
	bool enable;
	bool notCut;
	bool squint;
	eye_type m_eye_type;
	int squint_offset;

	int lateral_margins;

	ofxGifDecoder decoderCap;
	ofxGifFile cap;

	double ratioFrame;

	ofVideoGrabber *vidGrabber;
	vector<ofVideoDevice> devices;
	int indexCam;

	int camWidth;
	int camHeight;

	int rotate;
	string name;
	string nameUsedCam;

	bool showGui;
	ofxPanel gui;
	ofxLabel nameLabel;
	ofxToggle enableToggle;
	vector<ofxButton> camsButtons;
	vector<bool> camsClick;
	ofxLabel nameUsedCamLabel;
	ofxToggle notCutToggle;
	ofxToggle squintToggle;
	ofxIntSlider marginSlider;
	ofxButton rotatePlus;
	ofxButton rotateMinus;
};

