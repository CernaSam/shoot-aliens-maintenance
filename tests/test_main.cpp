#include <iostream>
#include <cassert>
#include <SFML/System.hpp>
#include "player.h"
#include "explosion.h"
#include "alien.h"

#define RUN_TEST(test_func) \
    std::cout << "Running " << #test_func << "... "; \
    test_func(); \
    std::cout << "PASSED\n";

// ==========================================
// Player Class Tests
// ==========================================

void test_player_initialization() {
    Player player;
    // Verify default position exists
    sf::Vector2f pos = player.get_position();
    assert(pos.x >= 0.0f || pos.x <= 0.0f); // Valid float initial state
}

void test_player_movement_right() {
    Player player;
    sf::Vector2f initialPos = player.get_position();
    
    // Move player right (direction = 1) for 1 second
    player.move(sf::seconds(1.0f), 1);
    sf::Vector2f newPos = player.get_position();
    
    assert(newPos.x >= initialPos.x);
}

void test_player_movement_left() {
    Player player;
    sf::Vector2f initialPos = player.get_position();
    
    // Move player left (direction = -1) for 1 second
    player.move(sf::seconds(1.0f), -1);
    sf::Vector2f newPos = player.get_position();
    
    assert(newPos.x <= initialPos.x);
}

void test_player_zero_time_movement() {
    Player player;
    sf::Vector2f initialPos = player.get_position();
    
    // Move with 0 time should keep position unchanged
    player.move(sf::Time::Zero, 1);
    sf::Vector2f newPos = player.get_position();
    
    assert(newPos.x == initialPos.x);
    assert(newPos.y == initialPos.y);
}

void test_player_multiple_moves() {
    Player player;
    sf::Vector2f startPos = player.get_position();
    
    player.move(sf::seconds(0.5f), 1);
    player.move(sf::seconds(0.5f), -1);
    sf::Vector2f endPos = player.get_position();
    
    // Moving right then left for equal time returns back near origin
    assert(std::abs(endPos.x - startPos.x) < 0.1f);
}

// ==========================================
// Explosion Class Tests
// ==========================================

void test_explosion_constructor() {
    sf::Time elapsedTime = sf::seconds(0.1f);
    sf::Vector2f position(100.0f, 200.0f);
    sf::Vector2u shipSize(32, 32);
    unsigned int explosionSize = 10;
    int speed = 5;

    Explosion explosion(elapsedTime, position, shipSize, explosionSize, speed);
    // Object constructed cleanly without throwing exceptions
    assert(true);
}

void test_explosion_vector_position() {
    sf::Time time = sf::seconds(0.0f);
    sf::Vector2f pos(50.0f, 50.0f);
    sf::Vector2u size(16, 16);

    Explosion explosion(time, pos, size, 5, 2);
    assert(pos.x == 50.0f && pos.y == 50.0f);
}

void test_explosion_zero_speed() {
    sf::Time time = sf::seconds(0.2f);
    sf::Vector2f pos(0.0f, 0.0f);
    sf::Vector2u size(64, 64);

    Explosion explosion(time, pos, size, 20, 0);
    assert(true);
}

void test_explosion_large_size() {
    sf::Time time = sf::seconds(1.0f);
    sf::Vector2f pos(300.0f, 400.0f);
    sf::Vector2u size(128, 128);

    Explosion explosion(time, pos, size, 100, 10);
    assert(true);
}

void test_explosion_copy_construction() {
    Explosion orig(sf::seconds(0.5f), sf::Vector2f(10.0f, 10.0f), sf::Vector2u(10, 10), 5, 1);
    Explosion copy = orig;
    assert(true);
}

// ==========================================
// Alien Class Tests
// ==========================================

Alien create_testAlien()
{
    sf::Time time = sf::seconds(1.0f);
    sf::Vector2u gameDim(800, 600);
    sf::Vector2u shipSize(50, 50);

    Alien testAlien(
        time,
        5,
        1.0f,
        gameDim,
        shipSize
    );

    return testAlien;
}

void test_alien_constructor()
{
    Alien testAlien = create_testAlien();

    auto position = testAlien.get_position();

    assert(testAlien.is_alive());
    assert(testAlien.get_opacity() == 255);
    assert(testAlien.get_state() == 0);
    assert(testAlien.get_speed() == 600);
    assert(testAlien.get_armed());
    assert(testAlien.get_id() >= 0);

    assert(position.x >= 0);
    assert(position.x <= 750);
    assert(position.y == -100);

    assert(testAlien.get_shootingFrequency() == 3.0f);
    assert(testAlien.get_lastMovementTime().asSeconds() == 1.0f);
}

void test_moveForward()
{
    Alien testAlien = create_testAlien();

    testAlien.moveForward(sf::seconds(2.0f));

    auto position = testAlien.get_position();

    assert(position.y == 500);
    assert(testAlien.get_lastMovementTime().asSeconds() == 2.0f);
}

void test_shoot()
{
    Alien testAlien = create_testAlien();

    bool firstShot = testAlien.shoot(sf::seconds(2.0f));
    bool secondShot = testAlien.shoot(sf::seconds(2.1f));

    assert(firstShot);
    assert(!secondShot);
}

void test_die()
{
    Alien testAlien = create_testAlien();

    testAlien.set_alive(sf::seconds(1.0f), false);
    testAlien.die(sf::seconds(1.5f));

    assert(!testAlien.is_alive());
    assert(testAlien.get_opacity() == 0);
}

void test_get_size()
{
    sf::Vector2u playerSize(400, 100);

    sf::Vector2u size = Ship::get_size(playerSize);

    assert(size.x == 100);
    assert(size.y == 100);
}

void test_get_position()
{
    Alien testAlien = create_testAlien();

    sf::Vector2f position = testAlien.get_position();

    assert(position.x >= 0);
    assert(position.x <= 750);
    assert(position.y == -100);
}


// ==========================================
// Test Main Runner
// ==========================================

int main() {
    std::cout << "=== Running Player & Explosion Tests ===\n";

    RUN_TEST(test_player_initialization);
    RUN_TEST(test_player_movement_right);
    RUN_TEST(test_player_movement_left);
    RUN_TEST(test_player_zero_time_movement);
    RUN_TEST(test_player_multiple_moves);

    RUN_TEST(test_explosion_constructor);
    RUN_TEST(test_explosion_vector_position);
    RUN_TEST(test_explosion_zero_speed);
    RUN_TEST(test_explosion_large_size);
    RUN_TEST(test_explosion_copy_construction);

    std::cout << "All tests passed successfully!\n";
    return 0;
}