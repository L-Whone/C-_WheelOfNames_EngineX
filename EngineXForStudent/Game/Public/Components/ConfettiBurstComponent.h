#pragma once
#include <memory>
#include <vector>
#include <random>
#include "Engine/Public/EngineTypes.h"

class Actor;

class ConfettiBurstComponent
{
public:
	ConfettiBurstComponent();

	void Spawn(const exVector2& originPosition, int numParticles);
	void Update(float deltaTime);
	void Clear();

private:
	struct ConfettiParticle
	{
		std::shared_ptr<Actor> actor;
		exVector2 velocity;
		float lifetimeRemaining = 0.0f;
	};

	std::vector<ConfettiParticle> mParticles;

	std::mt19937 mRng; // Random number generator

	float RandRange(float min, float max);
	int RandRangeInt(int min, int max);

	exColor RandomConfettiColor();
	exColor MakeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
};