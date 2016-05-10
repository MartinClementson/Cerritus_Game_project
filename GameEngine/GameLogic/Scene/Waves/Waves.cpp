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
	/*float pauseTime = 0;

	pauseTime += (float)deltaTime;

	while (pauseTime < 5)
	{

	}*/
}

void Waves::SetWaveGroup(int wave)
{
	this->waveNumber = wave;
}

int Waves::GetWaveGroup()
{
	return this->waveNumber;
}

void Waves::WaveInformation()
{
	int nextWave = 1;
	waveNumber = GetWaveGroup();
	switch (waveNumber) 
	{
		case 1:
			amountOfStandards = 2;
			SetWaveInformation(amountOfStandards);
			amountOFFast = 3;
			amountOfHealers = 5;
			break;
		case 2:
			amountOfStandards = 4;
			SetWaveInformation(amountOfStandards);
			amountOFFast = 2;
			amountOfHealers = 2;
			break;
		case 3:
			amountOfStandards = 8;
			SetWaveInformation(amountOfStandards);
			amountOFFast = 5;
			amountOfHealers = 2;
			//NextWave(nextWave);
			break;
		default: 
			amountOfStandards = 0;
			SetWaveInformation(amountOfStandards);
			break;
	}
}

void Waves::SpawnPositions(int spawnSwitch)
{
	XMFLOAT3 spawnPos;

	switch (spawnSwitch)
	{
	case 1:
		spawnPos = { -50.0f, 0.0f, 30.0f };
		SetSpawnPositions(spawnPos);
		break;
	case 2:
		spawnPos = { 20.0f, 0.0f, 30.0f };
		SetSpawnPositions(spawnPos);
		break;
	case 3:
		spawnPos = { -20.0f, 0.0f, -50.0f };
		SetSpawnPositions(spawnPos);
		break;
	default:
		spawnPos = { -40.0f, 0.0f, 40.0f };
		SetSpawnPositions(spawnPos);
		break;
	}
}

void Waves::NextWave(int nextWaveNumber)
{
	nextWaveNumber;
}

void Waves::SetWaveInformation(int amountOfEnemies)
{
	amountOfStandards = amountOfEnemies;
}

int Waves::GetWaveInformation()
{
	return amountOfStandards;
}

void Waves::SetSpawnPositions(XMFLOAT3 spawnPos)
{
	this->spawnPos = spawnPos;
}

XMFLOAT3 Waves::GetSpawnPositions()
{
	return spawnPos;
}