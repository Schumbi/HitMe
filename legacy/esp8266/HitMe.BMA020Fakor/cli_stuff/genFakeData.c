#include <stdio.h>
#include <math.h>

#include <stdint.h>
#include <stdlib.h>

/*
   This program generates some fake data to emulate testdata from the bma020 hitme sensor.
 */

union conv16_8_u
{
	uint16_t	data16x1;
	uint8_t		data8x2[2];
};

int16_t getData(double x)
{
	//double res = [x=-2:1](sin(-x**3)) * cos(x) * -1400
	double res = sin(-1*x*x*x) * cos(x) * -1400.0;
	return res;
}

void getTwoComFromDec(int16_t in, uint8_t* out, size_t size)
{
	union conv16_8_u conv;
	conv.data16x1 = (uint16_t)in & 1023;

	uint8_t d1 = conv.data8x2[0];
	uint8_t d2 = conv.data8x2[1];

	if(size >= 2)
	{
		out[1] = d1; // only 10bits required
		out[0] = d2;
	}

}

void printHead()
{
	printf(
			"#ifndef FAKEDATA_H \n"
			"#define FAKEDATA_H \n"
			"#include <stdint.h>\n"
		  );
}

void printEnd()
{
	printf(
			"};\n\n"
			"#endif // FAKEDATA_H\n"
		  );
}

void printTable(int steps)
{
	int min = -2;
	int max = 1;


	double stepWidth = (max - min) / (double)steps;
	double ctr = 0;

	const size_t bufSize = 2;
	const uint8_t valueBlockSize = bufSize * 3; // a in x,y,z dir as 2complement
	uint8_t buf[bufSize];

	int step = 0;

	printf(
			"extern uint16_t sizeData;\n"
			"uint16_t sizeData = %d;\n"
			"\n"
			"extern uint8_t data[];\n"
			"uint8_t data[] = {\n"
			, valueBlockSize*steps );

	for(ctr = min; ctr < max; ctr += stepWidth, step++)
	{
		int16_t in = getData(ctr);
		getTwoComFromDec(in, buf, bufSize);
		printf("%4d,%4d,",  buf[0], buf[1]);
		printf("%4d,%4d,",   buf[0], buf[1]);
		printf("%4d,%4d,", buf[0], buf[1]);
		printf(" // %3d %6d\n", step, in);
	}
}

int main(int argc, char**argv)
{
	int steps = 50;
	if(argc > 1)
	{
		steps = atoi(argv[1]);
	}

	printHead();
	printTable(steps);
	printEnd();

	return 0;
}
