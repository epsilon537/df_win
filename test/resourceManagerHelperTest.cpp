#include "ResourceManager.h"
#include "LogManager.h"

#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

int main(void) {
	int lineNbr, res;
	std::vector<std::string> v;
	std::string str;
	df::Frame frame;

	LM.startUp();
	LM.setLogToScreen();

	std::ifstream ifs;

	ifs.open("sprites/beginDelMissing.txt", std::ifstream::in);
	assert(ifs.good());

	lineNbr = 1;

	v = df::readData(&ifs, df::HEADER_TOKEN, lineNbr);
	assert(v.empty());

	ifs.close();

	ifs.open("sprites/endDelMissing.txt", std::ifstream::in);

	lineNbr = 1;

	v = df::readData(&ifs, df::HEADER_TOKEN, lineNbr);
	assert(v.empty());

	ifs.close();

	ifs.open("sprites/orig.txt", std::ifstream::in);

	lineNbr = 1;

	v = df::readData(&ifs, df::HEADER_TOKEN, lineNbr);
	assert(!v.empty());

	res = df::matchLineInt(&v, df::FRAMES_TOKEN.c_str());
	assert(res == 5);

	res = df::matchLineInt(&v, df::HEIGHT_TOKEN.c_str());
	assert(res == 2);

	res = df::matchLineInt(&v, df::WIDTH_TOKEN.c_str());
	assert(res == 6);

	res = df::matchLineInt(&v, df::SLOWDOWN_TOKEN.c_str());
	assert(res == 4);

	str = df::matchLineStr(&v, df::COLOR_TOKEN.c_str());
	assert(str == "green");

	v = df::readData(&ifs, df::BODY_TOKEN, lineNbr);

	frame = df::matchFrame(&v, 6, 2, lineNbr);
	assert(!frame.isEmpty());

	v = df::readData(&ifs, df::FOOTER_TOKEN, lineNbr);
	assert(!v.empty());

	res = df::matchLineInt(&v, df::VERSION_TOKEN.c_str());
	assert(res == 1);

	ifs.close();

	ifs.open("sprites/framesMissing.txt", std::ifstream::in);

	lineNbr = 1;

	v = df::readData(&ifs, df::HEADER_TOKEN, lineNbr);
	assert(!v.empty());

	res = df::matchLineInt(&v, df::FRAMES_TOKEN.c_str());
	assert(res == -1);

	ifs.close();

	ifs.open("sprites/colorMissing.txt", std::ifstream::in);

	lineNbr = 1;

	v = df::readData(&ifs, df::HEADER_TOKEN, lineNbr);
	assert(!v.empty());

	str = df::matchLineStr(&v, df::COLOR_TOKEN.c_str());
	assert(str.empty());

	ifs.close();

	ifs.open("sprites/incorrectWidth.txt", std::ifstream::in);

	lineNbr = 1;

	v = df::readData(&ifs, df::HEADER_TOKEN, lineNbr);
	v = df::readData(&ifs, df::BODY_TOKEN, lineNbr);
	assert(!v.empty());
	lineNbr = 9;
	frame = df::matchFrame(&v, 6, 2, lineNbr);
	assert(frame.isEmpty());

	ifs.close();

	ifs.open("sprites/missingEndFrame.txt", std::ifstream::in);

	lineNbr = 1;

	v = df::readData(&ifs, df::HEADER_TOKEN, lineNbr);
	v = df::readData(&ifs, df::BODY_TOKEN, lineNbr);
	assert(!v.empty());
	lineNbr = 9;

	frame = df::matchFrame(&v, 6, 2, lineNbr);
	assert(frame.isEmpty());

	ifs.close();

	LM.writeLog("Test Complete.\n");
	LM.shutDown();

	return 0;
}