#include "ofxUITattyXML.h"	
#include "ofXml.h"
#include "ofxUISuperCanvas.h"

void ofxUITattyXML::saveSettings(string fileName)
{
    ofXml XML;
    for(auto& canvas : canvas)
    {
        
    }
    
    XML.save(fileName);
}

void ofxUITattyXML::loadSettings(string fileName)
{
    ofXml XML;
    string message = "";

    if (!XML.load(fileName))
    {
        message = "Could not load file!";
        ofLogError() << message;
        return;
    }

    auto canvas = XML.getChild("canvas");
    while (canvas)
    {
        string name = canvas.getValue();
        ofxUISuperCanvas* superCanvas = new ofxUISuperCanvas(name);

        bool drawable = canvas.getBoolValue();
        superCanvas->setDrawable(drawable);

        auto button = canvas.getChild("button");
        while (button)
        {
            string name = button.getValue();
            ofxUIButton* btn = superCanvas->addButton(name, false);

            ofxUIDrawMode drawMode = (ofxUIDrawMode)button.getIntValue();
            btn->setDrawMode(drawMode);

            auto aabb = button.getChild("AABB");
            if (aabb)
            {
                int x = aabb.getChild("x").getIntValue();
                int y = aabb.getChild("y").getIntValue();
                int width = aabb.getChild("width").getIntValue();
                int height = aabb.getChild("height").getIntValue();
                btn->setAABB(x, y, width, height);
            }

            auto animation = button.getChild("animation");
            if (animation)
            {
                auto position = animation.getChild("position");
                if (position)
                {
                    int x = position.getChild("x").getIntValue();
                    int y = position.getChild("y").getIntValue();
                    ofPoint pos(x, y);
                    btn->setFrameAnimationPosition(pos);
                }

                auto imageOfHover = animation.getChild("imageOfHover");
                if (imageOfHover)
                {
                    string path = imageOfHover.getValue();
                    string folderName = imageOfHover.getChild("folderName").getValue();
                    string suffix = imageOfHover.getChild("suffix").getValue();
                    int num = imageOfHover.getChild("num").getIntValue();
                    btn->loadImageOfHover(path, folderName, suffix, num);
                }

                auto imageOfNormal = animation.getChild("imageOfNormal");
                if (imageOfNormal)
                {
                    string path = imageOfNormal.getValue();
                    string folderName = imageOfNormal.getChild("folderName").getValue();
                    string suffix = imageOfNormal.getChild("suffix").getValue();
                    int num = imageOfNormal.getChild("num").getIntValue();
                    btn->loadImageOfNormal(path, folderName, suffix, num);
                }

                auto imageOfPressed = animation.getChild("imageOfPressed");
                if (imageOfPressed)
                {
                    string path = imageOfPressed.getValue();
                    string folderName = imageOfPressed.getChild("folderName").getValue();
                    string suffix = imageOfPressed.getChild("suffix").getValue();
                    int num = imageOfPressed.getChild("num").getIntValue();
                    btn->loadImageOfPressed(path, folderName, suffix, num);
                }
            }

            auto label = button.getChild("label");
            if (label)
            {
                bool visible = label.getBoolValue();
                btn->getLabelWidget()->setVisible(visible);
            }

            button = button.getNextSibling("button");
        }

        canvas = canvas.getNextSibling("canvas");
    }

    if (!XML.getChild("canvas"))
    {
        message = "canvas: XML settings loaded";
        ofLogNotice() << message;
    }
}