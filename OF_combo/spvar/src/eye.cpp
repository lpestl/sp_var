#include "eye.h"
#ifdef TARGET_ANDROID
#include "ofxAndroidVideoGrabber.h"
#endif

void eye::setup(ofRectangle rect, vector<ofVideoDevice> deviceList, eye_type type, bool activate)
{
	enable = activate;

	mainRect = rect;
	viewRect = rect;

#ifdef TARGET_ANDROID
	decoderCap.decode("pics/giphy.gif");
#else
	decoderCap.decode("data\\pics\\giphy.gif");
#endif
	cap = decoderCap.getFile();

	lateral_margins = 10;
	ratioFrame = (double)cap.getWidth() / cap.getHeight();

	devices = deviceList;

	vidGrabber = NULL;
	indexCam = -1;

	camWidth = 640;//640;  // try to grab at this size.
	camHeight = 480;//480;

	rotate = 0;
	
	notCut = false;
	squint = false;

	m_eye_type = type;
	squint_offset = 0;

	switch (m_eye_type)
	{
	case eye_type::LEFT_EYE:
		name = "Left eye";
		break;
	case eye_type::RIGHT_EYE:
		name = "Right eye";
		break;
	default:
		name = "NONAME";
		break;
	}

	nameUsedCam = "Camera NONE";

	recalculateThePositionOfTheFrame();


	one_second_time = ofGetElapsedTimeMillis();
	camera_fps = 0;
	frames_one_sec = 0;

	// GUI settings
	showGui = false;
	
	marginSlider.addListener(this, &eye::changeMarginSlider);
	rotatePlus.addListener(this, &eye::rotatePlusClick);
	rotateMinus.addListener(this, &eye::rotateMinusClick);
	//notCutToggle.addListener(this, &eye::changeNotCut);
	//squintToggle.addListener(this, &eye::changeSquint);
	
	gui.setup(); // most of the time you don't need a name
	//ofxPanel gui;
	//ofxLabel nameLabel;
	gui.add(nameLabel.setup("name", name));
	//ofxToggle enableToggle;
	gui.add(enableToggle.setup("enable", enable));
	//vector<ofxButton> camsButtons;
	for (int i = 0; i < devices.size(); i++) {
		ofxButton btn;
		camsButtons.push_back(btn);
		camsClick.push_back(false);
	}
	ofxButton none_btn;
	camsButtons.push_back(none_btn);
	camsClick.push_back(false);
	
	for (int i = 0; i < camsButtons.size(); i++) {
		camsButtons[i].addListener(this, &eye::camButtonClick);
	}

	for (int i = 0; i < devices.size(); i++) {
		stringstream n;
		n << "Camera: " << devices[i].id << " " << devices[i].deviceName;
		gui.add(camsButtons[i].setup(n.str()));
	}
	gui.add(camsButtons[devices.size()].setup("None camera"));
	//ofxLabel nameUsedCamLabel;
	gui.add(nameUsedCamLabel.setup("used_cam", nameUsedCam));
	//ofxToggle notCutToggle;
	gui.add(notCutToggle.setup("not_cut", notCut));
	//ofxToggle squintToggle;
	gui.add(squintToggle.setup("squint", squint));
	//ofxIntSlider marginSlider;
	gui.add(marginSlider.setup("margin", lateral_margins, 0, mainRect.width / 2 - lateral_margins));
	gui.add(rotatePlus.setup("Rotated ON clockwise by 90 deg"));
	gui.add(rotateMinus.setup("Rotated COUNTER clockwise 90 deg"));
	gui.setPosition(mainRect.getCenter().x - gui.getWidth() / 2, mainRect.getCenter().y - gui.getHeight()/2);
}

void eye::update()
{
	enable = enableToggle;
	if (notCut != notCutToggle) changeNotCut();
	if (squint != squintToggle) changeSquint();

	if ((indexCam < 0) || (indexCam >= devices.size())) {
		nameUsedCam = "Camera NONE";
	}
	else {
		stringstream n;
		n << "Camera: " << devices[indexCam].id << " " << devices[indexCam].deviceName;
		nameUsedCam = n.str();
	}
	nameUsedCamLabel.setup("used_cam", nameUsedCam);

	for (int i = 0; i < camsButtons.size(); i++) {
		if ((camsButtons[i]) && (i != indexCam)) {
			camsClick[i] = true;
		}
	}

	if (enable) {
		if (indexCam >= 0) {
			if (vidGrabber != NULL) {
				vidGrabber->update();
				if (vidGrabber->isFrameNew()) {
					frames_one_sec++;
					if( ofGetElapsedTimeMillis() - one_second_time >= 1000){
						camera_fps = frames_one_sec;
						frames_one_sec = 0;
						one_second_time = ofGetElapsedTimeMillis();
					}
					ofPixels & pixels = vidGrabber->getPixels();
				}
			}
		}
	}
}

void eye::draw()
{
	drawBackground();

	if (enable) {
		ofSetColor(255, 255, 255);
		ofPushMatrix();
		//ofRotate(90, viewRect.x, viewRect.y, 0);
		ofTranslate(mainRect.getCenter());
		ofRotate(rotate);
		if (indexCam < 0) {			
			cap.draw(-viewRect.width / 2, -viewRect.height / 2 + squint_offset, viewRect.width, viewRect.height);
		}
		else {
			if (vidGrabber) {
				vidGrabber->draw(-viewRect.width / 2, -viewRect.height / 2 + squint_offset, viewRect.width, viewRect.height);
			}
		}
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(mainRect.getCenter());
		if (enable) {
			if (indexCam >= 0) {
				if (vidGrabber != NULL) {
					// Draw text gui
					ofSetColor(0, 0, 255, 100);
					ofDrawRectangle(mainRect.width / 2 - 350, 50 - mainRect.height / 2, 300, 100);
					ofSetColor(255, 255, 0, 255);
					ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), mainRect.width / 2 - 330, 70 - mainRect.height / 2);
					ofDrawBitmapString("camera fps: " + ofToString(camera_fps), mainRect.width / 2 - 330, 90 - mainRect.height / 2);
#ifdef TARGET_ANDROID
					ofDrawBitmapString("orientation: " + ofToString(orientation), mainRect.width - 330, 110 - mainRect.height / 2);
#endif
				}
			}
		}
		ofPopMatrix();
	}

	// finally, a report:
	stringstream reportStr;
	if (indexCam < 0) {
		ofSetHexColor(0xff0000);
		reportStr << "Camera NONE" << endl;
	}
	else {
		if (devices[indexCam].bAvailable) {
			ofSetHexColor(0x00ff00);
			reportStr << devices[indexCam].id << ": " << devices[indexCam].deviceName << endl;
		}
		else {
			ofSetHexColor(0xffff00);
			reportStr << devices[indexCam].id << ": " << devices[indexCam].deviceName << " - unavailable " << endl;
		}
	}
	ofDrawBitmapString(reportStr.str(), mainRect.x + 20, mainRect.y + 20);

#ifdef TARGET_ANDROID
	int wOrientation = ofOrientationToDegrees(ofGetOrientation());
	ofLogNotice()<<"Orientation: "<<ofGetOrientation()<<endl;
#endif

	ofPushMatrix();
	if (showGui) {
		gui.draw();
	}
	ofPopMatrix();
}

void eye::exit()
{
	for (int i = 0; i < camsButtons.size(); i++) {
		camsButtons[i].removeListener(this, &eye::camButtonClick);
	}
	//notCutToggle.removeListener(this, &eye::changeNotCut);
	//squintToggle.removeListener(this, &eye::changeSquint);
	rotatePlus.removeListener(this, &eye::rotatePlusClick);
	rotateMinus.removeListener(this, &eye::rotateMinusClick);
	marginSlider.removeListener(this, &eye::changeMarginSlider);
	camDelete();
	/*for (int i = 0; i < camsButtons.size(); i++) {
		delete camsButtons[i];
		camsButtons[i] = NULL;
	}
	camsButtons.clear();*/
}

void eye::drawBackground()
{
	if (enable) {
		ofSetColor(0, 0, 0);
		ofDrawRectangle(mainRect);
	}
}

void eye::setActive(bool activ)
{
	enable = activ;
}

void eye::setMargins(int margins)
{
	lateral_margins = margins;
	//viewRect.set(mainRect.x + margins, mainRect.y, mainRect.width - margins * 2, mainRect.height);
	recalculateThePositionOfTheFrame();
}

void eye::recalculateThePositionOfTheFrame()
{
	//else {
	//viewRect.x = mainRect.x + lateral_margins;
	viewRect.width = mainRect.width - lateral_margins * 2;
	viewRect.height = viewRect.width / ratioFrame;

	squint_offset = 0;
	//viewRect.y = mainRect.height / 2 - viewRect.height / 2;
	//}
	if ((rotate == 90) || (rotate == -90) || (rotate == 270) || (rotate == -270)) {
		//double k = viewRect.width / viewRect.height;
		viewRect.height = viewRect.width;
		viewRect.width = viewRect.height * ratioFrame;

		if (notCut) {
			if (viewRect.width > (mainRect.height - 2 * lateral_margins)) {
				viewRect.width = mainRect.height - 2 * lateral_margins;
				viewRect.height = viewRect.width / ratioFrame;

				if (squint) {
					switch (m_eye_type)
					{
					case eye_type::LEFT_EYE:
						squint_offset = (mainRect.width - viewRect.height) / 2 - lateral_margins;
						if ((rotate == 90) || (rotate == -270)) squint_offset *= -1;
						break;
					case eye_type::RIGHT_EYE:
						squint_offset = (mainRect.width - viewRect.height) / 2 - lateral_margins;
						if ((rotate == -90) || (rotate == 270)) squint_offset *= -1;
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void eye::changeCam(int index)
{
	//if (index < 0) return;
	camDelete();
	indexCam = index;
	camInit();
}

void eye::rotateImage(int addAngle)
{
	rotate += addAngle;
	if (rotate > 360) rotate -= -360;
	if (rotate < -360) rotate += 360;
	/*if ((rotate == 90) || (rotate == -90) || (rotate == 270) || (rotate == -270)) {
		ratioFrame = 1 / ratioFrame;
	} */
	recalculateThePositionOfTheFrame();
}

void eye::camButtonClick()
{
	for (int i = 0; i < camsButtons.size(); i++) {
		cout << camsClick[i];
		if ((camsClick[i]) && (i != indexCam)) {
			cout << "I want " << i << " camera" << endl;
			changeCam(i);
		}
		camsClick[i] = false;
	}
}

void eye::camInit()
{
	vidGrabber = new ofVideoGrabber();
	devices = vidGrabber->listDevices();
	if (indexCam >= devices.size()) {
		indexCam = -1;
		camDelete();
	}

	if (indexCam < 0) {
		ratioFrame = (double)cap.getWidth() / cap.getHeight();
		recalculateThePositionOfTheFrame();
		return;
	}
#ifdef TARGET_ANDROID
	// Set the pixel format for getPixels to monochrome
	// (other image formats will include heavy pixel conversion)
	//vidGrabber->setPixelFormat(OF_PIXELS_MONO);

	// Hint the grabber if you don't need pixel data for better performance
	//((ofxAndroidVideoGrabber*)grabber.getGrabber().get())->setUsePixels(false);

	// Start the grabber
	vidGrabber->setup(camWidth,camHeight);

	// Get the native android video grabber
	ofxAndroidVideoGrabber* androidGrabber = (ofxAndroidVideoGrabber*)vidGrabber->getGrabber().get();
	androidGrabber->setDeviceID(indexCam);

	// Get the orientation and facing of the current camera
	orientation = androidGrabber->getCameraOrientation();
	//facing = ((ofxAndroidVideoGrabber*)vidGrabber->getGrabber().get())->getFacingOfCamera();
#else
	vidGrabber->setDeviceID(indexCam);
	//vidGrabber->setDesiredFrameRate(60);
	vidGrabber->initGrabber(camWidth, camHeight);
#endif

	ratioFrame = (double)vidGrabber->getWidth() / vidGrabber->getHeight();
	recalculateThePositionOfTheFrame();
}

void eye::camDelete()
{
	if (indexCam >= 0) if (vidGrabber != NULL) {
		vidGrabber->close();
		delete vidGrabber;
		vidGrabber = NULL;
	}
}
