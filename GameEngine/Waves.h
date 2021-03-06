#pragma once
#ifndef WAVES_H
#define WAVES_H

#include "../../Source/LibIncluder.h"

using namespace DirectX;

class Waves
{
private:

private:

public:
	int waveNumber, switchSpawnPos;
	int amountOFFast, amountOfStandards, amountOfHealers;
	XMFLOAT3 spawnPos;
	~Waves();
	Waves();

	void Initialize();
	void Render();
	void Update(double deltaTime);

	int GetWaveGroup();
	void SetWaveGroup(int wave);

	void WaveInformation();
	void NextWave(int nextWaveNumber);
	void SetWaveInformation(int amountOfEnemies);
	int GetWaveInformation();
	void SpawnPositions(int spawnSwitch);
	void SetSpawnPositions(XMFLOAT3 spawnPos);
	XMFLOAT3 GetSpawnPositions();
};

#endif
