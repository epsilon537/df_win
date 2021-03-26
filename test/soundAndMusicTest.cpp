#include "Sound.h"
#include "Music.h"
#include <assert.h>
#include <stdio.h>
#include <Windows.h>

int main(void) {
	df::Sound sound;

	int res = sound.loadSound("does not exist");
	assert(res == -1);

	res = sound.loadSound("sounds\\explode.wav");
	assert(res == 0);

	sound.setLabel("explode");
	assert(sound.getLabel() == "explode");


	printf("Play.\n");
	sound.play();
	Sleep(3000);
	printf("Play looped.\n");
	sound.play(true);
	Sleep(3000);
	printf("Pause.\n");
	sound.pause();
	Sleep(2000);
	printf("Unpause.\n");
	sound.play();
	Sleep(2000);
	printf("Stop.\n");
	sound.stop();
	printf("Play again.\n");
	sound.play();
	Sleep(2000);

	df::Sound sound2;
	res = sound2.loadSound("sounds\\nuke.wav");
	assert(res == 0);
	printf("Play 2 sounds.\n");
	sound.play();
	sound2.play();
	Sleep(3000);
	sound.stop();
	sound2.stop();

	sound.getSound();

	df::Music music;

	res = music.loadMusic("does not exist");
	assert(res == -1);

	res = music.loadMusic("sounds\\start-music.wav");
	assert(res == 0);

	music.setLabel("start-music");
	assert(music.getLabel() == "start-music");

	printf("Play.\n");
	music.play();
	Sleep(3000);
	printf("Play looped.\n");
	music.play(true);
	Sleep(3000);
	printf("Pause.\n");
	music.pause();
	Sleep(2000);
	printf("Unpause.\n");
	music.play();
	Sleep(2000);
	printf("Stop.\n");
	music.stop();
	Sleep(2000);
	printf("Play again.\n");
	music.play();
	Sleep(2000);
	printf("Adding sounds.\n");
	sound.play();
	sound2.play();
	Sleep(3000);

	music.getMusic();

	printf("Test Complete.\n");
	return 0;
}