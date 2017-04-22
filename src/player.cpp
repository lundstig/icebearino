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
}

void Player::update(Game* game) {
    const auto leftKey = sf::Keyboard::Key::A;
    const auto rightKey = sf::Keyboard::Key::D;
    const auto runKey = sf::Keyboard::Key::W;
    const auto backKey = sf::Keyboard::Key::S;

    const float runSpeed = 150.0f;
    const float turnSpeed = 1.7f;

    sf::Vector2f forward = sf::Vector2f(cos(rot - M_PI / 2.0f), sin(rot - M_PI / 2.0f));

    bool moving = false;

    if (sf::Keyboard::isKeyPressed(runKey)) {
        pos += game->dt * forward * runSpeed;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(backKey)) {
        pos -= game->dt * forward * runSpeed * 0.4f;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(leftKey)) {
        rot -= game->dt * turnSpeed;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(rightKey)) {
        rot += game->dt * turnSpeed;
        moving = true;
    }

    if (moving && walkSound.getStatus() != sf::SoundSource::Status::Playing) {
        walkSound.play();
    }
    else if (!moving && walkSound.getStatus() == sf::SoundSource::Status::Playing) {
        walkSound.stop();
    }
}

void Player::render(Game* game) {
    sprite.setPosition(getRealPos(game));
    sprite.setRotation(rot * 180.0f / M_PI);
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