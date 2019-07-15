#ifndef H7SEGMENTS_PRIVATE_H
#define H7SEGMENTS_PRIVATE_H

	enum segment {A=0, B, C, D, E, F, G};
	unsigned int numbers[11][8] = {
			{A,B,C,D,E,F,-1},		// 0
			{B,C,-1},				// 1
			{A,B,E,D,G,-1},			// 2
			{A,B,C,D,G,-1},			// 3
			{B,C,F,G,-1},			// 4
			{A,C,D,F,G,-1},			// 5
			{A,C,D,E,F,G,-1},		// 6
			{A,B,C,-1},				// 7
			{A,B,C,D,E,F,G,-1}, 	// 8
			{A,B,C,D,F,G,-1},		// 9
			{E,F}
	};

#endif
