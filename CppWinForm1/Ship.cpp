#ifndef INCLUDED_IOS
#define INCLUDED_IOS
#include <iostream>
#endif

class Ship {
public: short length; // length of ship, how far it goes from point of origin
		short width; // width of ship, does it bleed into adjacent spaces, only 1 allowed so far
		short xCoord; // point of origin
		short yCoord; // point of origin
		short orientation; // 1 = west, 2 = north, 3 = east, 4 = south. If a ship has width>1, even widths will protrude east/south
		short hp; // how many hits left to sunk. by default initialized to width*length

		Ship(short l, short w, short x, short y, short or ) {
			length = l;
			if (w != 1) { std::cout << "width is only allowed to be 1" << std::endl; }
			width = 1;
			xCoord = x;
			yCoord = y;
			orientation = or ;
			hp = length * width;
		}

		// returns remaining hp
		int hit(int x, int y) {
			return --hp;
		}
};