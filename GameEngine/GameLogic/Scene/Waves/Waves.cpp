#include "./Waves.h"

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
	waveNumber = GetWaveGroup();
	switch (waveNumber)
	{
	case 1:
		amountOfStandards = 10;
		SetWaveInformation(amountOfStandards);
		/*	amountOFFast = 3;
		amountOfHealers = 5;*/
		break;
	case 2:
		amountOfStandards = 0;
		SetWaveInformation(amountOfStandards);
		/*		amountOFFast = 2;
		amountOfHealers = 2;*/
		break;
	case 3:
		amountOfStandards = 0;
		SetWaveInformation(amountOfStandards);
		/*	amountOFFast = 5;
		amountOfHealers = 2;*/
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
		spawnPos = { -70.0f, 0.0f, 40.0f };
		SetSpawnPositions(spawnPos);
		break;
	case 2:
		spawnPos = { 70.0f, 0.0f, 40.0f };
		SetSpawnPositions(spawnPos);
		break;
	case 3:
		spawnPos = { 40.0f, 0.0f, -70.0f };
		SetSpawnPositions(spawnPos);
		break;
	case 4:
		spawnPos = { -70.0f, 0.0f, -40.0f };
		SetSpawnPositions(spawnPos);
		break;
	default:
		spawnPos = { -70.0f, 0.0f, 40.0f };
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