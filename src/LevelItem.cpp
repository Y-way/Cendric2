#include "LevelItem.h"
#include "MainCharacter.h"

void LevelItem::loadItem(MainCharacter* mainChar, LevelItemID id)
{
	m_mainChar = mainChar;
	m_itemID = id;
}

void LevelItem::load()
{
	// nop
}

void LevelItem::onRightClick()
{
	// check if item is in range
	sf::Vector2f dist = m_mainChar->getCenter() - getCenter();
	if (sqrt(dist.x * dist.x + dist.y * dist.y) <= m_pickupRange)
	{
		// TODO pickup, create the correct item in the players inventory.
		setDisposed();
	}
	else
	{
		m_screen->setTooltipText(g_textProvider->getText(Texts::Warn_itemTooFarAway), sf::Vector2f(10.f, 10.f), sf::Color::Red);
	}
}

void LevelItem::onMouseOver()
{
	m_animatedSprite.setColor(sf::Color::Red);
	m_screen->setTooltipText(m_tooltipText, sf::Vector2f(10.f, 10.f), sf::Color::White);
}

void LevelItem::render(sf::RenderTarget &renderTarget)
{
	GameObject::render(renderTarget);
	m_animatedSprite.setColor(sf::Color::White);
}

GameObjectType LevelItem::getConfiguredType() const
{
	return GameObjectType::_LevelItem;
}

void LevelItem::setTooltipText(const std::string& tooltip)
{
	m_tooltipText = tooltip;
}

sf::Color LevelItem::getConfiguredDebugColor() const
{
	return sf::Color::Cyan;
}
