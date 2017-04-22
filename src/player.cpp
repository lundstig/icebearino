#include "penguin.h"
#include "util.h"
#include <math.h>

Player::Player(int icefloe) {
    loadTexture(texture, "res/img/bear.png");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

    loadSoundBuffer(walkSoundBuffer, "res/sound/walk.ogg");
    walkSound.setBuffer(walkSoundBuffer);
    walkSound.setLoop(true);

    this->icefloe = icefloe;
    pos = sf::Vector2f(0.0f, 0.0f);
    rot = 0.0f;
    height = 0.0f;
    vel = sf::Vector2f(0.0f, 0.0f);
    velY = 0.0f;
}

void Player::update(Game* game) {
    const auto leftKey = sf::Keyboard::Key::A;
    const auto rightKey = sf::Keyboard::Key::D;
    const auto runKey = sf::Keyboard::Key::W;
    const auto backKey = sf::Keyboard::Key::S;
    const auto jumpKey = sf::Keyboard::Key::Space;

    float runSpeed = 600.0f - length(vel);
    const float reverseFraction = 0.25f;
    const float turnSpeed = 1.7f;
    const float friction = 3.0f;

    sf::Vector2f forward = sf::Vector2f(cos(rot - M_PI / 2.0f), sin(rot - M_PI / 2.0f));

    bool moving = false;

    // Move forward/backward
    if (height == 0.0f) {
        if (sf::Keyboard::isKeyPressed(runKey)) {
            vel += game->dt * forward * runSpeed;
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(backKey)) {
            vel -= game->dt * forward * runSpeed * reverseFraction;
            moving = true;
        }
    }
    // Rotate left/right
    if (sf::Keyboard::isKeyPressed(leftKey)) {
        rot -= game->dt * turnSpeed;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(rightKey)) {
        rot += game->dt * turnSpeed;
        moving = true;
    }

    // Update position and velocity
    pos += vel * game->dt;
    if (height == 0.0f)
        vel -= vel * friction * game->dt;

    // Walk sound
    if (moving && walkSound.getStatus() != sf::SoundSource::Status::Playing) {
        walkSound.play();
    }
    else if (!moving && walkSound.getStatus() == sf::SoundSource::Status::Playing) {
        walkSound.stop();
    }

    // Jumping
    if (height == 0.0f && sf::Keyboard::isKeyPressed(jumpKey)) {
        velY = 1.5f;
    }
    height += velY * game->dt;
    velY -= 5.0f * game->dt;
    if (height < 0.0f) {
        velY = height = 0.0f;
    }
}

void Player::render(Game* game) {
    sprite.setPosition(getRealPos(game));
    sprite.setRotation(rot * 180.0f / M_PI);
    float scale = 1.0f + height;
    sprite.setScale(scale, scale);
    drawSprite(sprite, game);
}

sf::Vector2f Player::getRealPos(Game* game) {
    sf::Vector2f realPos = pos;

    if (icefloe != -1) {
        Icefloe* floe = game->icefloes[icefloe];
        realPos += floe->pos;
    }

    return realPos;
}
