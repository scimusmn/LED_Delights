/*
 *  controlBar.cpp
 *  LED_Delights
 *
 *  Created by Exhibits on 11/30/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "controlBar.h"

extern ofColor gray, black, white, red, orange, yellow, blue;

void controlBar::setup(imageArea & img)
{
  image=&img;
  
  mode=LED_HOME;
  
  redo.setup(64, 64, "images/redo.png");
	undo.setup(64,64,"images/undo.png");
  
  drawB.setup(256, OF_HOR, "images/draw.png");
	demo.setup(256,OF_HOR, "images/demo.jpg");
	predef.setup(256, OF_HOR, "images/predef.jpg");
  
  home.setup("New user?", 20);
  
  uploadBut.setup("Send image to wheel", 25);
  
  drawImage.loadImage("upload/images/0.jpg");
  
  upload.setup(image);
  
  toolBar::setup(OF_HOR);
  area.width=w=ofGetWidth();
  addSegment(20, &undo,&redo);
  addSegment(0, &uploadBut);
  addSegment(30, &home);
}

void controlBar::draw(int _x, int _y)
{
  x=_x,y=_y;
  ofSetColor(gray);
  ofRect(area);
  ofSetColor(black);
  drawHatching(area.x, area.y, area.width, area.height, 50, 50);
  objHolder::draw(_x,_y);
}

void controlBar::drawForeground()
{
  int mouseX=ofGetAppPtr()->mouseX;
  int mouseY=ofGetAppPtr()->mouseY;
  if(mode==LED_HOME){
    ofSetColor(gray);
    ofRectangle r(0,0,ofGetWidth(),ofGetHeight());
    ofRect(r);
    ofSetColor(black);
    drawHatching(r.x, r.y, r.width, r.height, 15, 1);
    predef.draw((ofGetWidth()/2-predef.w)/2, (ofGetHeight()-predef.h)/2);
    drawB.draw((ofGetWidth()-drawB.w)/2,(ofGetHeight()-drawB.h)/2);
    demo.draw((3*ofGetWidth()/2-demo.w)/2,(ofGetHeight()-demo.h)/2);
  }
  upload.drawForeground();
}

void controlBar::update()
{
  
}

void controlBar::setAvailableButtons()
{
  if(mode==LED_DRAW){
    redo.setAvailable(drawImage.redoAvailable());
    undo.setAvailable(drawImage.undoAvailable());
  }
}

bool controlBar::clickDown(int _x, int _y, int button)
{
  if(mode!=LED_HOME){
    if(home.clickDown(_x, _y)) image->mode=mode=LED_HOME;
  }
  else{
    if(drawB.clickDown(_x, _y)) image->mode=mode=LED_DRAW, image->changeImage(drawImage);
    else if(demo.clickDown(_x, _y)) image->mode=mode=LED_DEMO;
    else if(predef.clickDown(_x, _y)) image->mode=mode=LED_PREDEF;
  }
  if(mode==LED_DRAW){
    if(undo.clickDown(_x, _y)) drawImage.undo();
    else if(redo.clickDown(_x, _y)) drawImage.redo();
  }
  if(mode==LED_DRAW||mode==LED_PREDEF) 
    if(uploadBut.clickDown(_x, _y)) upload.upload();
}

bool controlBar::clickUp()
{
  home.clickUp();
  drawB.clickUp();
  demo.clickUp();
  predef.clickUp();
  image->clickUp();
  
  undo.clickUp();
  redo.clickUp();
  
  uploadBut.clickUp();
  
  setAvailableButtons();
}

bool controlBar::mouseLockout(int button)
{
  
}
