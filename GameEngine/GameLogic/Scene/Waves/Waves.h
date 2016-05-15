#pragma once
#ifndef WAVES_H
#define WAVES_H

#include "../../Source/LibIncluder.h"

using namespace DirectX;

class Waves
{
private:
	int waveNumber = 0;
	float waveTimer = 0;

public:
	int switchSpawnPos = 0;
	bool winCondition = false;

	int amountOFFast, amountOfStandards, amountOfHealers;
	float posAdd;
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
	void SetSpawnPosAdd(float add);
	float GetSpawnPosAdd();
	void SetWaveInformation(int amountOfEnemies);
	int GetWaveInformation();
	void SpawnPositions(int spawnSwitch);
	void SetSpawnPositions(XMFLOAT3 spawnPos);
	XMFLOAT3 GetSpawnPositions();

	float GetWaveTimer() { return this->waveTimer; }
	void SetWinCondition(bool win);
	bool GetWinCondition();
};

#endif

