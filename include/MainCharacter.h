#pragma once

#include "global.h"
#include "MovableGameObject.h"
#include "Level.h"
#include "InputController.h"
#include "SpellManager.h"
#include "Screen.h"

// Cendric in a level
class MainCharacter : public MovableGameObject
{
public:
	MainCharacter(Level* level);
	~MainCharacter();

	void load() override;
	void update(const sf::Time& frameTime) override;
	void checkCollisions(const sf::Vector2f& nextPosition) override;
	void calculateUnboundedVelocity(const sf::Time& frameTime, sf::Vector2f& nextVel) const override;

	float getConfiguredMaxVelocityY() const override;
	float getConfiguredMaxVelocityX() const override;
	GameObjectType getConfiguredType() const override;
	Level* getLevel() const;
	bool getIsFacingRight() const;
	GameObjectState getState() const;
	sf::Color getConfiguredDebugColor() const override;

private:
	const float WALK_ACCELERATION = 1500.0f;
	const float GRAVITY_ACCELERATION = 1000.0f;
	// choose a value between 0.9 for really slow halting and 1.0f for aprupt halting.
	const float DAMPING_GROUND_PER_S = 0.999f;
	const float DAMPING_AIR_PER_S = 0.7f;

	// handle input and calculate the next position
	void handleInput();
	// update animation based on the current velocity + grounded
	void updateAnimation();
	bool m_isFacingRight;
	bool m_nextIsFacingRight;
	bool m_isGrounded;
	Level* m_level;

	SpellManager* m_spellManager;
	// as long as this time is not sf::Time::Zero, cendric will have the fighting animation. 
	sf::Time m_fightAnimationTime;
};