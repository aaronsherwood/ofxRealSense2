#include "ofxRealSense2.h"
#include "ofxRealSense2Utils.h"


ofxRealSense2::ofxRealSense2(){
}

ofxRealSense2::~ofxRealSense2(){
}

bool ofxRealSense2::setup(){
    pipe.start();
    colorImage.allocate(COLOR_WIDTH, COLOR_HEIGHT, OF_IMAGE_COLOR);
    depthImage.allocate(DEPTH_WIDTH, DEPTH_HEIGHT, OF_IMAGE_COLOR);
}

void ofxRealSense2::update(){
    rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
    rs2::frame depth = color_map(data.get_depth_frame()); // Find and colorize the depth data
    rs2::frame color = data.get_color_frame();            // Find the color data
    
    colorImage.setFromPixels((unsigned char *)color.get_data(), COLOR_WIDTH, COLOR_HEIGHT, OF_IMAGE_COLOR);
    depthImage.setFromPixels((unsigned char *)depth.get_data(), DEPTH_WIDTH, DEPTH_HEIGHT, OF_IMAGE_COLOR);
    
}


//----------------------------------------------------------
void ofxRealSense2::draw(float _x, float _y, float _w, float _h) const{
    colorImage.draw(_x, _y, _w, _h);
}

//----------------------------------------------------------
void ofxRealSense2::draw(float _x, float _y) const{
    draw(_x, _y, (float)COLOR_WIDTH, (float)COLOR_HEIGHT);
}

//----------------------------------------------------------
void ofxRealSense2::draw(const ofPoint & point) const{
    draw(point.x, point.y);
}

//----------------------------------------------------------
void ofxRealSense2::draw(const ofRectangle & rect) const{
    draw(rect.x, rect.y, rect.width, rect.height);
}

//----------------------------------------------------------
void ofxRealSense2::drawDepth(float _x, float _y, float _w, float _h) const{
    depthImage.draw(_x, _y, _w, _h);
}

//---------------------------------------------------------------------------
void ofxRealSense2::drawDepth(float _x, float _y) const{
    drawDepth(_x, _y, (float)DEPTH_WIDTH, (float)DEPTH_HEIGHT);
}

//----------------------------------------------------------
void ofxRealSense2::drawDepth(const ofPoint & point) const{
    drawDepth(point.x, point.y);
}

//----------------------------------------------------------
void ofxRealSense2::drawDepth(const ofRectangle & rect) const{
    drawDepth(rect.x, rect.y, rect.width, rect.height);
}


ofPixels & ofxRealSense2::getPixels(){
    return colorImage.getPixels();
}

ofPixels & ofxRealSense2::getDepthPixels(){
    return depthImage.getPixels();
}
