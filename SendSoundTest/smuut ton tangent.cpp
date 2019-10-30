#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

constexpr auto C3 = 130.81;
constexpr auto D3 = 146.83;
constexpr auto E3 = 164.81;
constexpr auto F3 = 174.61;
constexpr auto G3 = 196;
constexpr auto A3 = 220;
constexpr auto B3 = 246.93;
constexpr auto C4 = 261.63;
constexpr auto D4 = 293.66;
constexpr auto E4 = 329.63;
constexpr auto F4 = 349.23;
constexpr auto G4 = 392;
constexpr auto A4 = 440;
constexpr auto B4 = 493.88;

int notsomain() {

	//float TUNES[] = { F4, A4, G4, G4, E4, G4, F4, F4, D4, F4, E4, E4, C4, D4, A3, A3};	//asgors theme
	//float TUNES[] = { C4, G4, F4, C4, E4, 0, E4, F4,0, C4, F4, C4, E4,0, E4, F4, C4, G4, F4, C4, E4, 0, E4, F4,0, C4, F4, A4, G4, 0, F4, G4 }; //undertale theme
	//float TUNES[] = { C4, C4, 1, 1, A4, G4,  1, C4, C4, 1, 1, 1, 1, C4, C4, 1, 1, A4, G4, 1, D4, D4, 1, 1, D4, D4, C4, 1, C4, 1, 1, A4, G4, C4, C4, 1, 1, 1, 1,  E4, 1, E4, C4, D4, E4, C4, D4, E4, C4, D4, E4, C4, D4 };//may be shelter
	float TUNES[] = { 73,  73,  73,  73,  73,  73 };

	float BPM = 120;
	const unsigned toneCount = sizeof(TUNES) / sizeof(*TUNES);

	float BPS = BPM / 60;
	const unsigned SAMPLES = 1000 * 8 * toneCount;
	unsigned SAMPLE_RATE = (SAMPLES / toneCount)*BPS;
	int samplePerTone = SAMPLES / toneCount;

	unsigned AMPLITUDE = 20000;
	sf::Int16 raw[SAMPLES];
	double increment;
	double x = 0;				//sine funktion variable 
	sf::SoundBuffer Buffer;		//define sound buffer
	sf::Sound Sound;			//define Sound output
	sf::OutputSoundFile FILE;	//define file
	const double TWO_PI = 6.28318;
	const double PI = 3.14159;
	float preVal = 0; //previous value
	float curVal = 0; //current value

	for (int j = 0; j < toneCount; j++)
	{

		//check for pause in music
		if (TUNES[j] == 0 || TUNES[j] == 1)
			increment = 1;
		else
			increment = (TUNES[j]) / SAMPLE_RATE;


		//generate sine function
		x = 0;
		unsigned start = (samplePerTone)*j;
		unsigned slut = (j + 1)*(samplePerTone);
		preVal = curVal; // saving previous value
		if (curVal - preVal < 0) 
		{
			for (unsigned i = start; i < slut; i++)
			{
				raw[i] = AMPLITUDE * sin(x*TWO_PI);
				x += increment;
				curVal = AMPLITUDE * sin(x*TWO_PI);
			}
		}
		else
		{
			for (unsigned i = start; i < slut; i++)
			{
				raw[i] = AMPLITUDE * sin(x*TWO_PI + PI);
				x += increment;
				curVal = AMPLITUDE * sin(x*TWO_PI + PI);
			}
		}


	}
	//load sound to bufffer
	if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE))
	{
		std::cerr << "Loading failed!" << std::endl;
		return 1;
	}

	//output sound
	Sound.setBuffer(Buffer);
	std::cout << "playing sound " << "\n";
	Sound.play();


	////write file
	//if (!FILE.openFromFile("testSounds.ogg", 44100, 1))
	//	std::cout << "could not save to file\n";
	//else
	//	FILE.write(raw, SAMPLES);

	//wait x milliseconds 'til next tone
	sf::sleep(sf::seconds(toneCount / BPS));
	return 0;
}
