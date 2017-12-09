#include "Level/MOBBehavior/MovingBehaviors/VeliusVictimMovingBehavior.h"
#include "Level/Enemies/VeliusVictim.h"

const sf::Vector2f VeliusVictimMovingBehavior::ALTAR_POS = sf::Vector2f(670.f, 600.f);

VeliusVictimMovingBehavior::VeliusVictimMovingBehavior(VeliusVictim* enemy) :
	MovingBehavior(enemy),
	EnemyMovingBehavior(enemy),
	WalkingBehavior(enemy) {
	m_victim = enemy;
}

void VeliusVictimMovingBehavior::execHandleMovementInput() {
	auto state = m_mob->getState();
	if (state == GameObjectState::Inactive || state == GameObjectState::Broken) {
		m_movingDirectionX = 0;
		m_movingDirectionY = 0;
		m_mob->setVelocity(sf::Vector2f(0.f, 0.f));
		return;
	}
	
	gotoTarget(ALTAR_POS, 10.f, true, true);

	if (dist(ALTAR_POS, m_victim->getPosition()) < 10.f) {
		m_mob->setState(GameObjectState::Broken);
	}
}

void VeliusVictimMovingBehavior::updateAnimation(const sf::Time& frameTime) {
	GameObjectState newState = GameObjectState::Idle;
	auto state = m_mob->getState();
	if (state == GameObjectState::Inactive || state == GameObjectState::Broken) {
		newState = state;
	}
	else if (m_enemy->isDead()) {
		newState = GameObjectState::Dead;
	}
	else if (!m_isGrounded) {
		newState = GameObjectState::Jumping;
	}
	else if (std::abs(m_enemy->getVelocity().x) > 20.f) {
		newState = GameObjectState::Walking;
	}

	// only update animation if we need to
	if (m_enemy->getState() != newState || (m_nextIsFacingRight != m_isFacingRight)) {
		m_isFacingRight = m_nextIsFacingRight;
		m_enemy->setState(newState);
		m_enemy->setCurrentAnimation(m_enemy->getAnimation(m_enemy->getState()), !m_isFacingRight);
	}
}

void VeliusVictimMovingBehavior::callToDie() {
	m_mob->setState(GameObjectState::Idle);
}
