#include "SpellCreators/IceBallSpellCreator.h"
#include "Screens/LevelScreen.h"

IceBallSpellCreator::IceBallSpellCreator(const SpellBean &spellBean, LevelMovableGameObject *owner) : SpellCreator(spellBean, owner)
{
	m_allowedModifiers.push_back(SpellModifierType::Damage);
	m_allowedModifiers.push_back(SpellModifierType::Count);
	m_allowedModifiers.push_back(SpellModifierType::Reflect);
	m_allowedModifiers.push_back(SpellModifierType::Speed);
}

void IceBallSpellCreator::executeSpell(const sf::Vector2f &target)
{
	SpellBean spellBean = m_spellBean;
	updateDamage(spellBean);
	int div = 0;
	int sign = 1;
	for (int i = 0; i < m_spellBean.count; i++)
	{
		IceBallSpell* newSpell = new IceBallSpell();
		newSpell->load(spellBean, m_owner, target, div * sign * spellBean.divergenceAngle);
		m_screen->addObject(newSpell);
		sign = -sign;
		if (sign == -1)
		{
			div += 1;
		}
	}

	m_owner->setFightAnimationTime();
}