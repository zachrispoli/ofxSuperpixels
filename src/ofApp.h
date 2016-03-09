#pragma once

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
using namespace std;

#include "slic.h"

#include "ofxCvColorImage.h"

#include "ofxDatGui.h"
#include "ofMain.h"

#define INIT_N_SUPERPIXELS 100
#define INIT_N_WEIGHT_FACTOR 100
#define IMG_RESIZE_SIZE 800

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void onSliderEvent(ofxDatGuiSliderEvent e);
    
    void generateSuperpixels(ofImage img, int nr_superpixels, int nc);
    
    ofxDatGui *gui;
    
    int nSuperpixels;
    int nWeightFactors;
    
    ofImage img;
    ofxCvColorImage dogCvColorImg;
		
};
