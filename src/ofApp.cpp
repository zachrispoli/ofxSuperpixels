#include "ofApp.h"

void ofApp::setup(){
    
    /* setup gui */
    
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->setWidth(500);
    gui->addSlider("superpixels", 0, 500, INIT_N_SUPERPIXELS);
    gui->addSlider("weight factors", 0, 500, INIT_N_WEIGHT_FACTOR);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    nSuperpixels = INIT_N_SUPERPIXELS;
    nWeightFactors = INIT_N_WEIGHT_FACTOR;
    
    /* generate superpixels on example image */
    
    img.load("dog.jpg");
    generateSuperpixels(img, 100, 100);
    
}

void ofApp::update(){
    
}

void ofApp::draw(){
    
    dogCvColorImg.draw(ofGetWidth()/2 - img.getWidth()/2,
                       ofGetHeight()/2 - img.getHeight()/2);
    
}

void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){
    
    generateSuperpixels(img, nSuperpixels, nWeightFactors);
    
}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo info) {
    
    img.load(info.files.at(0));
    
    ofVec2f wh = ofVec2f(img.getWidth(),
                         img.getHeight());
    wh.normalize();
    img.resize(wh.x*IMG_RESIZE_SIZE,
               wh.y*IMG_RESIZE_SIZE);
    
    generateSuperpixels(img, nSuperpixels, nWeightFactors);
    
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {

    if(e.target->getLabel() == "SUPERPIXELS") {
        nSuperpixels = e.value;
    } else if(e.target->getLabel() == "WEIGHT FACTORS") {
        nWeightFactors = e.value;
    }
    
}

/* Written by: Pascal Mettes.
 *
 * This file creates an over-segmentation of a provided image based on the SLIC
 * superpixel algorithm, as implemented in slic.h and slic.cpp. */

void ofApp::generateSuperpixels(ofImage img, int nr_superpixels, int nc) {
    
    /* Load the image and convert to Lab colour space. */
    dogCvColorImg.setFromPixels(img.getPixels(), img.getWidth(), img.getHeight());
    IplImage *image = dogCvColorImg.getCvImage();
    IplImage *lab_image = cvCloneImage(image);
    cvCvtColor(image, lab_image, CV_BGR2Lab);
    
    int w = image->width, h = image->height;
    
    double step = sqrt((w * h) / (double) nr_superpixels);
    
    /* Perform the SLIC superpixel algorithm. */
    Slic slic;
    slic.generate_superpixels(lab_image, step, nc);
    slic.create_connectivity(lab_image);
    
    /* Display the contours and show the result. */
    slic.display_contours(image, CV_RGB(0,0,255));
    //slic.colour_with_cluster_means(image);
    //cvShowImage("result", image);
    //cvWaitKey(0);
    //cvSaveImage("newdoggie.png", image);
    
}
