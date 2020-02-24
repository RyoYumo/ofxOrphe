#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(800, 600);
    
    ofCreateWindow(settings);
    ofRunApp(std::make_shared<ofApp>());
        

}
