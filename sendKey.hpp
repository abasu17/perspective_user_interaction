/*
 * sendKey.hpp
 * 
 * Copyright 2015 Aniket Basu;
 * 
 * This is a .hpp file; which contains some functions
 * with the name of SendKey(), evntNext(), evntPrev(), evntZoomIN()
 * evntZoomOUT(); Those functions can be used to perform some 
 * system call or Events.
 * 
 * this functions contains some pre-defined X11 functions; 
 * these functions are user defined functions.
 */
 
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>
#include <stdio.h>

Display *disp = XOpenDisplay (0);
Window focus;
int revert;

//Send Fake Key Event
static void SendKey (Display * disp, KeySym keysym, KeySym modsym){
	KeyCode keycode = 0, modcode = 0;
	keycode = XKeysymToKeycode (disp, keysym);
	if (keycode == 0) return;
	XTestGrabControl (disp, True);
	/* Generate modkey press */
	if (modsym != 0) {
		modcode = XKeysymToKeycode(disp, modsym);
		XTestFakeKeyEvent (disp, modcode, True, 0);
		XTestFakeKeyEvent (disp, keycode, True, 0);
		XTestFakeKeyEvent (disp, keycode, False, 0);
		XTestFakeKeyEvent (disp, modcode, False, 0);
		}
	/* Generate regular key press and release */	
	else if (modsym == 0){	
		XTestFakeKeyEvent (disp, keycode, True, 0);
		XTestFakeKeyEvent (disp, keycode, False, 0); 
		}
	//~ /* Generate modkey release */
	//~ if (modsym != 0)
		//~ XTestFakeKeyEvent (disp, modcode, False, 0);
 
	XSync (disp, False);
	XTestGrabControl (disp, False);
}
 
/* Next Function */
void evntNext(){
	XGetInputFocus(disp, &focus, &revert);
	printf("%ld\n",focus);
	
	//Send ASCII
	XSetInputFocus(disp, focus, revert, CurrentTime);
	SendKey (disp, 0xff53 , 0);
	}

/* Previous Function */
void evntPrev(){
	XGetInputFocus(disp, &focus, &revert);
	printf("%ld\n",focus);
	
	//Send ASCII
	XSetInputFocus(disp, focus, revert, CurrentTime);
	SendKey (disp, 0xff51 , 0);
	}


/* ZoomIN Function */
void evntZoomIN(){
	XGetInputFocus(disp, &focus, &revert);
	printf("%ld\n",focus);
	
	//Send ASCII
	XSetInputFocus(disp, focus, revert, CurrentTime);
	SendKey (disp, 0xffab , 0);
	}
	
/* ZoomOUT Function */
void evntZoomOUT(){
	XGetInputFocus(disp, &focus, &revert);
	printf("%ld\n",focus);
	
	//Send ASCII
	XSetInputFocus(disp, focus, revert, CurrentTime);
	SendKey (disp, 0xffad , 0);
	}

/* ZoomIN Move Right*/
void evntZoomINMoveR(){
	XGetInputFocus(disp, &focus, &revert);
	printf("%ld\n",focus);
	
	//Send ASCII
	XSetInputFocus(disp, focus, revert, CurrentTime);
	SendKey (disp, 0xff53, 0xffea);
	}

/* ZoomIN Move Left*/
void evntZoomINMoveL(){
	XGetInputFocus(disp, &focus, &revert);
	printf("%ld\n",focus);
	
	//Send ASCII
	XSetInputFocus(disp, focus, revert, CurrentTime);
	SendKey (disp, 0xff51, 0xffea);
	}

/* ZoomIN Move Up*/
void evntZoomINMoveU(){
	XGetInputFocus(disp, &focus, &revert);
	printf("%ld\n",focus);
	
	//Send ASCII
	XSetInputFocus(disp, focus, revert, CurrentTime);
	SendKey (disp, 0xff97, 0xffea);
	}

/* ZoomIN Move Down*/
void evntZoomINMoveD(){
	XGetInputFocus(disp, &focus, &revert);
	printf("%ld\n",focus);
	
	//Send ASCII
	XSetInputFocus(disp, focus, revert, CurrentTime);
	SendKey (disp, 0xff99, 0xffea);
	}
