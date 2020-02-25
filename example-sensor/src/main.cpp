#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(1550, 1000);
    
    ofCreateWindow(settings);
    ofRunApp(std::make_shared<ofApp>());
        

}
