#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

std::vector<float> EN = { 1209, 697 };
std::vector<float> TO = { 1336, 697 };
std::vector<float> TRE = { 1477, 697 };
std::vector<float> A = { 1633, 697 };
std::vector<float> FIRE = { 1209, 770 };
std::vector<float> FEM = { 1336, 770 };
std::vector<float> SEKS = { 1477, 770 };
std::vector<float> B = { 1633, 770 };
std::vector<float> SYV = { 1209, 852 };
std::vector<float> OTTE = { 1336, 852 };
std::vector<float> NI = { 1477, 852 };
std::vector<float> C = { 1633, 852 };
std::vector<float> STJERNE = { 1209, 941 };
std::vector<float> NUL = { 1336, 941 };
std::vector<float> HAVELÅG = { 1447, 941 };
std::vector<float> D = { 1633, 941 };




int main() {
	std::vector<std::vector<float>> TUNES = { D };
	std::string filename;

	const unsigned toneCount = TUNES.size();

	float BPS = 1;		//tones per second cannot be under 1
	const unsigned SAMPLES = 44100; 
	unsigned SAMPLE_RATE = (SAMPLES / toneCount)*BPS;
	int samplePerTone = SAMPLES / toneCount;

	unsigned AMPLITUDE = 10000;
	sf::Int16 raw[SAMPLES];
	double incrementX;
	double incrementY;
	double x = 0, y = 0;		//sine funktion variable  
	sf::SoundBuffer Buffer;		//define sound buffer
	sf::Sound Sound;			//define Sound output
	sf::OutputSoundFile FILE;	//define file
	x = 0;
	y = 0;
	const double TWO_PI = 6.28318;
	for (int j = 0; j < toneCount; j++)
	{
		unsigned start = (samplePerTone)*j;
		unsigned slut = (j + 1)*(samplePerTone);

		
		//generate sine function
		for (unsigned i = start; i < slut; i++) { // loop for every sample
			raw[i] = AMPLITUDE * sin(x*TWO_PI) + AMPLITUDE * sin(y*TWO_PI);
			x += TUNES[j][0] / SAMPLE_RATE;
			y += TUNES[j][1] / SAMPLE_RATE;
					
		}

		//load sound to bufffer
		if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
			std::cerr << "Loading failed!" << std::endl;
			return 1;
		}

		//output sound
		Sound.setBuffer(Buffer);
		std::cout << "playing sound " << TUNES[j][0] << " and " << TUNES[j][1] << "\n";
		////write file generate DTMF wave files
		//	filename = "";
		//	filename.append("DTMF");
		//	filename.append(std::to_string(j));
		//	filename.append(".wav");
		//	if (!FILE.openFromFile(filename, 44100, 1))
		//		std::cout << "could not save to file\n";
		//	else
		//		FILE.write(raw, SAMPLES);

		//wait x milliseconds 'til next loop
		
	}
	Sound.play();
	sf::sleep(sf::seconds((toneCount / BPS)));

	if (!FILE.openFromFile("DTMF.wave", SAMPLES, 1))
		std::cout << "could not save to file\n";
	else
		FILE.write(raw, SAMPLES);
	return 0;
}