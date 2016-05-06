#include "Waves.h"

Waves::Waves()
{
	
}

Waves::~Waves()
{

}

void Waves::Initialize()
{
	
}

void Waves::Render()
{

}

void Waves::Update(double deltaTime)
{

}

void Waves::SetWave(int wave)
{
	this->waveNumber = wave;
}

int Waves::GetWave()
{
	return this->waveNumber;
}

void Waves::WaveInformation()
{
	waveNumber = GetWave();
	switch (waveNumber) 
	{
		case 1:
			amountOfStandards = 2;
			SetWaveInformation(amountOfStandards);
			amountOFFast = 3;
			amountOfHealers = 5;
			break;
		case 2:
			amountOfStandards = 2;
			amountOFFast = 2;
			amountOfHealers = 2;
			break;
		case 3:
			amountOfStandards = 4;
			amountOFFast = 5;
			amountOfHealers = 2;
			break;
		default: 

			break;
	}
}

void Waves::SetWaveInformation(int amountOfEnemies)
{
	amountOfStandards = amountOfEnemies;
}

int Waves::GetWaveInformation()
{
	return amountOfStandards;
}

//Waves * Waves::GetInstance()
//{
//	static Waves instance;
//	return &instance;
//}
//
