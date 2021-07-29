#include "enemy.h"
#include "player.h"
#include "Math/MathUtil.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "player")
	{
		destroy = true;
		std::vector<nc::Color> colorsButGood = { nc::Color::red, nc::Color::white, nc::Color::blue };
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 100, 2, colorsButGood[rand() % colorsButGood.size()], 150);

		nc::Event event;

		event.name = "AddPoints";
		event.data = 100;
		scene->engine->Get<nc::EventSystem>()->Notify(event);

		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
	}
}

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	if (scene->GetActor<Player>())
	{
		nc::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		nc::Vector2 forward = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation);

		float turnAngle = nc::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (3 * dt);

		float angle = nc::Vector2::Angle(forward, direction.Normalized());

		//transform.rotation += nc::QuarterPi;
		transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
		transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
		transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

		transform.Update();
		fireTimer -= dt;

		if (doesShoot) {
			if (fireTimer <= 0 and angle <= nc::DegToRad(15))
			{
				fireTimer = fireRate;
				//std::vector<nc::Vector2> points = { {-5,-5}, {5,-5}, {5,5}, {-5,5}, {-5,-5} };
				//std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>(points, nc::Color{ nc::Random(), nc::Random(), nc::Random() });
				//std::shared_ptr<nc::Shape> shape = scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("hammer.txt");
				
				nc::Transform t = transform;
				t.scale = .75f;
				t.rotation += nc::HalfPi;

				std::cout << "fire\n";
				std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("bullet.txt"), 300.0f);
				projectile->tag = "enemy";
				scene->AddActor(std::move(projectile));
				
				scene->engine->Get<nc::AudioSystem>()->PlayAudio("enemyShoot");
			}
		}
	}
}