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

	//static Waves* GetInstance();

	~Waves();
	Waves();


	void Initialize();
	void Render();
	void Update(double deltaTime);

	int GetWave();
	void SetWave(int wave);
	
	void WaveInformation();
	void SetWaveInformation(int amountOfEnemies);
	int GetWaveInformation();
	void TimeBetweenWaves();
};

#endif