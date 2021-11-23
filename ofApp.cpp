#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofNoFill();
	ofSetLineWidth(1.5);
	ofSetCircleResolution(60);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->base_radius = 150;
	for (int deg = 0; deg < 360; deg++) {

		this->base_location_list.push_back(glm::vec3(this->base_radius * cos(deg * DEG_TO_RAD), this->base_radius * sin(deg * DEG_TO_RAD) - 150, 0));
	}
}

//--------------------------------------------------------------
void ofApp::update() {


	int radius = 6;
	ofColor color;
	while (this->log_list.size() < 800) {

		int font_location_index = ofRandom(this->base_location_list.size());
		vector<glm::vec2> log;
		log.push_back(this->base_location_list[font_location_index]);
		this->log_list.push_back(log);

		color.setHsb((ofGetFrameNum() * 2) % 255, 200, 100);
		this->color_list.push_back(color);

		this->life_list.push_back(ofRandom(10, 200));
	}

	for (int i = this->log_list.size() - 1; i >= 0; i--) {

		this->life_list[i] -= 1;
		if (this->life_list[i] < 0) {

			this->log_list.erase(this->log_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);

			continue;
		}

		auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.008, ofGetFrameNum() * 0.0015)), 0, 1, 45, 125 + 10);
		this->log_list[i].push_back(this->log_list[i].back() + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
		while (this->log_list[i].size() > 100) {

			this->log_list[i].erase(this->log_list[i].begin());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int i = 0; i < this->log_list.size(); i++) {

		ofSetColor(this->color_list[i], this->life_list[i] > 30 ? 255 : ofMap(this->life_list[i], 0, 30, 0, 255));

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}	

	ofSetColor(255);
	ofDrawCircle(glm::vec3(0, -150, 0), 150);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}