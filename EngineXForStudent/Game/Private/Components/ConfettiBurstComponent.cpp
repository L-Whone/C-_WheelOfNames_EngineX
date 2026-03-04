#include "Game/Public/Components/ConfettiBurstComponent.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/RenderComponent.h"
#include "Game/Public/Components/RectangleRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include <algorithm>
#include <chrono>

float ConfettiBurstComponent::RandRange(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(mRng);
}

int ConfettiBurstComponent::RandRangeInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mRng);
}

exColor ConfettiBurstComponent::RandomConfettiColor()
{
    //Conffetti colors
    static exColor palette[] = {
        { 255, 215,  64, 255 },
        { 255,  99, 132, 255 },
        {  72, 209, 204, 255 },
        {  50, 205,  50, 255 },
        { 186,  85, 211, 255 },
        { 255, 165,   0, 255 },
        { 255,  69,   0, 255 },
        {  30, 144, 255, 255 },
    };

    int idx = RandRangeInt(0, (int)(sizeof(palette) / sizeof(palette[0])) - 1);
    return palette[idx];
}

exColor ConfettiBurstComponent::MakeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    exColor color;
    color.mColor[0] = r;
    color.mColor[1] = g;
    color.mColor[2] = b;
    color.mColor[3] = a;
    return color;
}

ConfettiBurstComponent::ConfettiBurstComponent()
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count(); // Get a seed based on the current time
	mRng = std::mt19937(seed); // Initialize the random number generator with the seed
}

void ConfettiBurstComponent::Spawn(const exVector2& originPosition, int numParticles)
{
	mParticles.reserve(mParticles.size() + numParticles); // Reserve space for new particles

    for (int i = 0; i < numParticles; i++) 
    {
        auto confettiPiece = Actor::SpawnActorOfType<Actor>(originPosition); // spawn actor

		// Get random sizes for each confetti particle
		float width = RandRange(5.0f, 25.0f);
		float height = RandRange(5.0f, 25.0f);

		exColor color = RandomConfettiColor(); // Get a random color for each confetti particle

		confettiPiece->AddComponentOfType<RectangleRenderComponent>(color, height, width); // Add render component to actor

		// Set random velocity for each confetti particle
        exVector2 velocity;
		velocity.x = RandRange(-300.0f, 300.0f); // Random horizontal velocity
        velocity.y = RandRange(-400.0f, 100.0f); // Random upward velocity

		// Sets lifetime for each confetti particle
        float lifetime = RandRange(2.0f, 4.0f);

        // Sets the particle's properties
		ConfettiParticle particle;
        particle.actor = confettiPiece;
        particle.velocity = velocity;
        particle.lifetimeRemaining = lifetime;

		mParticles.push_back(particle); // Add the new particle to the list
    }
}

void ConfettiBurstComponent::Update(float deltaTime)
{
    const float gravity = 900.0f;
    const float drag = 0.98f;          // air resistence
    const float floorY = 600.0f + 40.0f;

    for (auto& particle : mParticles)
    {
        if (particle.actor) // Check if the actor is still valid
        {
			particle.lifetimeRemaining -= deltaTime; // substract lifetime remaining
			particle.velocity.y += gravity * deltaTime; // Apply gravity to vertical velocity

            // Drag
			particle.velocity.x *= drag;
            particle.velocity.y *= drag;

			// Update position
			auto transform = particle.actor->GetComponentOfType<TransformComponent>();

            if (transform)
            {
                exVector2 newPosition = transform->GetLocation() + particle.velocity * deltaTime;

                //// Check for collision with the floor
                //if (newPosition.y > floorY)
                //{
                //    newPosition.y = floorY; // Snap to the floor
                //    particle.velocity.y *= -0.5f; // Bounce with some energy loss
                //    particle.velocity.x *= 0.7f; // Reduce horizontal velocity on bounce
                //}
                transform->SetLocation(newPosition);
            }
        }

		// Remove particle if its lifetime has expired
        mParticles.erase(
            std::remove_if(mParticles.begin(), mParticles.end(),
                [](const ConfettiParticle& p)
                {
                    return (!p.actor) || (p.lifetimeRemaining <= 0.0f);
                }),
            mParticles.end()
        );
    }
}

void ConfettiBurstComponent::Clear()
{
    for(auto& particle : mParticles) particle.actor.reset(); // Reset shared_ptr to destroy the actor
	mParticles.clear(); // Clear the particle list
}

