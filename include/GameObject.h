#pragma once

#include <map>

#include "global.h"
#include "AnimatedSprite.h"
#include "InputController.h"

#include "Enums/GameObjectState.h"
#include "Enums/GameObjectType.h"

class Screen;

// A game object with animations, position, bounding box, game state. 
class GameObject 
{
public:
	GameObject();
    virtual ~GameObject() {}

	virtual void update(const sf::Time& frameTime);
	virtual void render(sf::RenderTarget& renderTarget);
	// used for tooltips and loot windows
	virtual void renderAfterForeground(sf::RenderTarget& renderTarget);
	// gets checked & called in the update loop. default implementation does nothing.
	// checks for the bounding box 
	virtual void onMouseOver();
	// gets checked & called in the update loop. default implementation does nothing.
	// checks for the bounding box 
	// right click is used to interact with game objects
	virtual void onRightClick();
	// left click is used to fire spells / press buttons
	virtual void onLeftClick();
	virtual void onRightJustPressed();
	virtual void onLeftJustPressed();
	virtual void onInteractKey();

	void addAnimation(GameObjectState state, Animation& animation);

	void setBoundingBox(const sf::FloatRect& rect);
	virtual void setPosition(const sf::Vector2f& pos);
	void setPositionX(float posX);
	void setPositionY(float posY);
	void setDisposed();
	void setCurrentAnimation(const Animation* animation, bool isFlipped);
	void setSpriteOffset(const sf::Vector2f& spriteOffset);
	void setScreen(Screen* screen);
	void setFrameTime(const sf::Time& time);
	// angle is in radian
	void setRotation(float angle);
	void playCurrentAnimation(bool play);
	void loopCurrentAnimation(bool loop);

	const Animation* getAnimation(GameObjectState state);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSpriteOffset() const;
	const sf::FloatRect* getBoundingBox() const;
	const sf::Vector2f getCenter() const;
	// returns whether the game object should be deleted
	// if this is set, the game object gets deleted in the next game loop
	bool isDisposed() const;
	virtual GameObjectType getConfiguredType() const = 0;
	Screen* getScreen() const;
	void setDebugBoundingBox(const sf::Color &debugColor);

	// convenience method for updating time values (used in many GOs). 
	// The frame time is subtracted from the time but 
	// if the time falls below sf::Time::Zero, it is set to sf::Time::Zero.
	static void updateTime(sf::Time &time, const sf::Time &frameTime);

protected:
	GameObjectState m_state;
	sf::Vector2f m_nextPosition;
	AnimatedSprite m_animatedSprite;
	Screen* m_screen = nullptr;
	
protected:
	bool m_isDisposed = false;

	std::map<GameObjectState, Animation> m_animations;
	sf::Vector2f m_spriteOffset;
	sf::FloatRect m_boundingBox;
	// absolute position as seen from the upper left corner
	sf::Vector2f m_position;

private:
	bool m_isDrawBoundingBox = false;
	sf::RectangleShape m_debugBox;
};