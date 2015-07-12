#pragma once

#include "global.h"
#include "MovableGameObject.h"
#include "Structs/AttributeBean.h"

class Level;
class SpellManager;
class Spell;

// a MOB in a level, enemies + main character.
class LevelMovableGameObject : public MovableGameObject
{
public:
	LevelMovableGameObject(Level* level);
	~LevelMovableGameObject();

	virtual void update(const sf::Time& frameTime) override;
	virtual void checkCollisions(const sf::Vector2f& nextPosition) override;
	// the offset to the from where a spell starts. it gets added to the spell offset defined by the spell itself. default is (0,0)
	virtual sf::Vector2f getConfiguredSpellOffset() const;
	void calculateUnboundedVelocity(const sf::Time& frameTime, sf::Vector2f& nextVel) const override;
	virtual void onHit(Spell* spell);
	// adds damage to the attribute health. this damage can be negative (heal)
	void addDamage(int damage);
	// sets the dead bool and sets the attribute health to zero.
	void setDead();

	SpellManager* getSpellManager() const;
	Level* getLevel() const;
	bool getIsFacingRight() const;
	bool isDead() const;
	GameObjectState getState() const;

protected:

	virtual float getConfiguredWalkAcceleration() const;
	virtual float getConfiguredGravityAcceleration() const;
	// choose a value between 0.9 for really slow halting and 1.0f for aprupt halting.
	virtual float getConfiguredDampingGroundPersS() const;
	virtual float getConfiguredDampingAirPerS() const;
	// handle input and calculate the next position (AI or user input)
	virtual void handleMovementInput() = 0;
	virtual void handleAttackInput() = 0;
	virtual void setSpriteColor(const sf::Color& color, const sf::Time& time);
	// update animation based on the current velocity + grounded
	void updateAnimation();
	bool m_isFacingRight;
	bool m_nextIsFacingRight;
	bool m_isGrounded = false;
	bool m_isDead = false;
	Level* m_level;

	SpellManager* m_spellManager;
	// as long as this time is not sf::Time::Zero, the mob will have the fighting animation. 
	sf::Time m_fightAnimationTime = sf::Time::Zero;
	// the sprite will reset its color as soon as this time is zero.
	sf::Time m_coloredTime = sf::Time::Zero;

	AttributeBean* m_attributes;

	// regeneration (hp)
	void updateRegeneration(const sf::Time& frameTime);
	sf::Time m_timeSinceRegeneration = sf::Time::Zero;
};