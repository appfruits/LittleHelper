# LittleHelper
This is the Arduino compatible firmware running Little Helper, a little device that is useful in electronic labs. The firmware also shows how to build a more complex LCD based application, featuring a few standard controls.

This software should compile and run on a Teensy 3.1 although you will need a few hardware components to make use of it. Have a look at http://www.appfruits.com/littlehelper. We provide everything from PCB schematics and layout, even enclosings to build your own Little Helper or getting inspired building your own little, useful device.

Copyright 2014-2015 by Phillip Schuster
http://www.appfruits.com

## Structure
This software is C++ and shows how to build a nice, stack based application runloop and User Interface that is easily expandable by providing standard controls and protocols and uses the good old MVC structure. 

Running such code on a small 8-bit AVR is overkill, but with all those new ARM MCUs offering a lot of performance, and more importantly offering more RAM allows such code to be written and run even on small devices. This makes it easier to write structured software that you can read in a couple of months from now.

## License
We provide this in a MIT-License. You may use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software but you must include this copyright notice and this permission in all copies or substantial portions of the Software.

We invest time and resources making this open source. Please support us by spreading your word and purchasing our products.
