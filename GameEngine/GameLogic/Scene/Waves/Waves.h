#pragma once
#ifndef WAVES_H
#define WAVES_H

class Waves
{
private:

private:

public:
	int waveNumber;
	int amountOFFast, amountOfStandards, amountOfHealers;

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
};

#endif