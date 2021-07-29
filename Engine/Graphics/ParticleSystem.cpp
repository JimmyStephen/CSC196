#include "ParticleSystem.h"
#include "Math/Random.h"

namespace nc
{
	void ParticleSystem::Startup()
	{
		//Death
		//particles.resize(10000000000000000000);
		//ONE MILLION MWAHAHAHAHHA
		// works ish but with lag
		//particles.resize(1000000);
		//750k
		//particles.resize(750000);
		//500k
		//particles.resize(500000);
		//Actually 10000
		particles.resize(10000);
		//Actually 1000
		//particles.resize(1000);
	}

	void ParticleSystem::Shutdown()
	{
		particles.clear();
	}
	
	void ParticleSystem::Update(float dt)
	{
		for (Particle& particle : particles)
		{
			particle.lifetime -= dt;
			particle.isActive = particle.lifetime > 0;
			particle.prevPosition = particle.position;
			particle.velocity *= .9;
			particle.velocity.y += 5;
			particle.position += particle.velocity * dt;
		}
	}
	
	void ParticleSystem::Draw(Core::Graphics& graphics)
	{
		for (const Particle& particle : particles)
		{
			if (particle.isActive) {
				graphics.SetColor(particle.color);
				graphics.DrawLine(particle.position.x, particle.position.y, particle.prevPosition.x, particle.position.y);
			}
		}
	}
	
	void ParticleSystem::Create(const Vector2& position, size_t count, float lifetime, const Color& color, float speed)
	{
		for (size_t i = 0; i < count; i++)
		{
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::isNotActive);
			if (particle != particles.end())
			{
				particle->isActive = true;
				particle->lifetime = lifetime;
				particle->position = position;
				particle->prevPosition = position;
				particle->color = color;

				particle->velocity = Vector2{ RandomRange(-1,1), RandomRange(-1,1) } * ((speed * Random()) * 2);

			}
		}
	}
}