#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Math/MathUtil.h"
#include "Engine.h"
#include "Game.h"
#include <memory>
#include <vector>

Player::Player(const nc::Transform transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed }
{
    std::unique_ptr locator = std::make_unique<Actor>();
    locator->transform.localPosition = nc::Vector2{ 0,4 };
    AddChild(std::move(locator));

    locator = std::make_unique<Actor>();
    locator->transform.localPosition = nc::Vector2{ 4,0 };
    AddChild(std::move(locator));

    locator = std::make_unique<Actor>();
    locator->transform.localPosition = nc::Vector2{ -4,0 };
    AddChild(std::move(locator));
}

void Player::OnCollision(Actor* actor)
{
    if ((dynamic_cast<Enemy*>(actor) && immunityFrameTimer <= 0) || ((dynamic_cast<Projectile*>(actor) && actor->tag == "enemy") && immunityFrameTimer <= 0))
    {
        //destroy = true;
        nc::Event event;
        event.name = "PlayerDead";
        scene->engine->Get<nc::EventSystem>()->Notify(event);
        immunityFrameTimer = immunityFrames;
    }
}

void Player::Update(float dt)
{
    Actor::Update(dt);

    //movement
    float thrust = 0;
    if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
    if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
    if (Core::Input::IsPressed('W')) thrust = speed;

    //nc::Vector2 acceleration;
    //acceleration += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * thrust;

    //nc::Vector2 gravity = (nc::Vector2{ 400,300 } - transform.position).Normalized() * 20;
    //acceleration += gravity;

    //velocity += (acceleration * dt) / 4;
    //transform.position += velocity;
    //velocity *= .9;

    transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * thrust * dt;
    transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
    transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

    //fire
    fireTimer -= dt;
    immunityFrameTimer -= dt;
    if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
    {
        std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>();
        shape->Load("star.txt");

        {
            nc::Transform t = children[0]->transform;
            t.scale = 3;

            std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, shape, 300.0f);
            projectile->tag = "player";
            
            scene->AddActor(std::move(projectile));
        }

        //side guns
        //{
        //    nc::Transform t = children[1]->transform;
        //    t.scale = .75f;
        //    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, shape, 300.0f);
        //    projectile->tag = "player";
        //    scene->AddActor(std::move(projectile));
        //}
        //{
        //    nc::Transform t = children[2]->transform;
        //    t.scale = .75f;
        //    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, shape, 300.0f);
        //    projectile->tag = "player";
        //    scene->AddActor(std::move(projectile));
        //}

        scene->engine->Get<nc::AudioSystem>()->PlayAudio("playerShoot");

        fireTimer = fireRate;
    }

    transform.Update();
}
