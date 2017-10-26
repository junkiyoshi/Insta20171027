#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(255);
	ofSetWindowTitle("Insta");

	ofSetColor(0);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 50);
	this->moji = "";

	this->box2d.init();
	this->box2d.setGravity(0, 10);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
		
	this->eage = ofxBox2dEdge();
	this->eage.addVertex(ofVec2f(200, ofGetHeight() / 2));
	this->eage.addVertex(ofVec2f(ofGetWidth() - 200, ofGetHeight() / 2));
	this->eage.create(this->box2d.getWorld());

	this->moji_x = 25;
	this->moji_y = 50;
}

//--------------------------------------------------------------
void ofApp::update() {
	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (int i = 0; i < this->moji.size(); i++) {
		ofPushMatrix();
		ofTranslate(this->rects[i].get()->getPosition().x, this->rects[i].get()->getPosition().y);
		ofRotate(this->rects[i].get()->getRotation());
		ofSetColor(this->rects_color[i]);
		this->font.drawString((this->moji.substr(i, 1)), -this->font.stringWidth(this->moji.substr(i, 1)) / 2, this->font.stringHeight(this->moji.substr(i, 1)) / 2);
		ofPopMatrix();
	}

	this->eage.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (this->moji_x > ofGetWidth()) {
		this->moji_x = 25;
	}

	// Enter
	if (key == 13) {
		this->moji_x = 25;
	}

	// Space
	if (key == 32) {
		this->moji_x += 25;
	}

	// Character
	if (key >= 32 && key < 127) {
		char key_c = (char)key;
		string new_moji{ key_c };
		this->moji += new_moji;
		this->rects.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
		this->rects.back().get()->setPhysics(3.0, 0.5, 0.1);
		this->rects.back().get()->setup(this->box2d.getWorld(), this->moji_x, this->moji_y, this->font.stringWidth(new_moji), this->font.stringHeight(new_moji));

		ofColor rect_color;
		rect_color.setHsb(ofGetFrameNum() % 255, 255, 255);
		this->rects_color.push_back(rect_color);

		this->moji_x += this->font.stringWidth(new_moji) * 1.1;
	}
	
	
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}