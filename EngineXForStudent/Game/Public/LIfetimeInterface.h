#pragma once

class ILifetimeInterface
{
public:
	virtual void BeginPlay() = 0;
	virtual void EndPlay()=  0;
	virtual void Tick(const float DeltaTime) = 0;

};