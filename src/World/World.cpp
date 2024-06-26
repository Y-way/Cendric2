#include "World/World.h"

World::World() {
}

World::~World() {
	dispose();
}

void World::dispose() {
	m_foregroundTileMap.dispose();
	m_backgroundTileMap.dispose();
	m_lightedForegroundTileMap.dispose();
}

void World::update(const sf::Time& frameTime) {
	m_backgroundTileMap.update(frameTime);
	m_foregroundTileMap.update(frameTime);
	m_lightedForegroundTileMap.update(frameTime);
}

void World::drawBackground(sf::RenderTarget& target, const sf::RenderStates& states) const {
	m_backgroundTileMap.draw(target, states);
}

void World::drawLightedForeground(sf::RenderTarget& target, const sf::RenderStates& states) const {
	m_lightedForegroundTileMap.draw(target, states);
}

void World::drawForeground(sf::RenderTarget& target, const sf::RenderStates& states) const {
	m_foregroundTileMap.draw(target, states);
}

const TileMap* World::getBackgroundTileMap() const {
	return &m_backgroundTileMap;
}

const TileMap* World::getLightedForegroundTileMap() const {
	return &m_lightedForegroundTileMap;
}

const TileMap* World::getForegroundTileMap() const {
	return &m_foregroundTileMap;
}

const sf::FloatRect& World::getWorldRect() const {
	return m_worldData->mapRect;
}

bool World::collidesWithCollidableLayer(const sf::Vector2f& pos) const {
	int x = static_cast<int>(std::round(pos.x) / TILE_SIZE_F);
	int y = static_cast<int>(std::round(pos.y) / TILE_SIZE_F);
	if (y < 0 || y > m_worldData->mapSize.y - 1) return true;
	if (x < 0 || x > m_worldData->mapSize.x - 1) return true;

	return m_worldData->collidableTilePositions[y][x];
}

bool World::collides(WorldCollisionQueryRecord& rec) const {
	rec.collides = false;
	rec.safeLeft = rec.collisionDirection == CollisionDirection::Left ? 0.f : m_worldData->mapRect.width;
	rec.safeTop = rec.collisionDirection == CollisionDirection::Up ? 0.f : m_worldData->mapRect.height;
	rec.movingParent = nullptr;
	const sf::FloatRect& bb = rec.boundingBox;
	// check for collision with map rect (x axis. y axis is not checked in levels, only in maps)
	if (bb.left < m_worldData->mapRect.left || bb.left + bb.width > m_worldData->mapRect.left + m_worldData->mapRect.width) {
		if (rec.collisionDirection == CollisionDirection::Right) {
			rec.safeLeft = std::min(rec.safeLeft, m_worldData->mapRect.left + m_worldData->mapRect.width - bb.width);
		}
		if (rec.collisionDirection == CollisionDirection::Left) {
			rec.safeLeft = std::max(rec.safeLeft, m_worldData->mapRect.left);
		}
		rec.collides = true;
	}

	// normalize bounding box values so they match our collision grid. Wondering about the next two lines? Me too. We just don't want to floor values that are exactly on the boundaries. But only those that are down and right.
	int bottomY = static_cast<int>(floor((bb.top + bb.height) / TILE_SIZE_F) == (bb.top + bb.height) / TILE_SIZE_F ? (bb.top + bb.height) / TILE_SIZE_F - 1 : floor((bb.top + bb.height) / TILE_SIZE_F));
	int rightX = static_cast<int>(floor((bb.left + bb.width) / TILE_SIZE_F) == (bb.left + bb.width) / TILE_SIZE_F ? (bb.left + bb.width) / TILE_SIZE_F - 1 : floor((bb.left + bb.width) / TILE_SIZE_F));
	sf::Vector2i topLeft(static_cast<int>(floor(bb.left / TILE_SIZE_F)), static_cast<int>(floor(bb.top / TILE_SIZE_F)));
	sf::Vector2i topRight(rightX, static_cast<int>(floor(bb.top / TILE_SIZE_F)));
	sf::Vector2i bottomLeft(static_cast<int>(floor(bb.left / TILE_SIZE_F)), bottomY);
	sf::Vector2i bottomRight(rightX, bottomY);

	// check level grid
	for (int x = topLeft.x; x <= topRight.x; x++) {
		for (int y = topLeft.y; y <= bottomLeft.y; y++) {
			if (y >= static_cast<int>(m_worldData->collidableTilePositions.size()) || y < 0 || x < 0 || x >= static_cast<int>(m_worldData->collidableTilePositions[y].size())) {
				// check for out of range (happens seldom because of rounding problems above)
				continue;
			}
			if (m_worldData->collidableTilePositions[y][x]) {
				if (rec.collisionDirection == CollisionDirection::Right) {
					rec.safeLeft = std::min(rec.safeLeft, x * TILE_SIZE_F - bb.width);
				}
				if (rec.collisionDirection == CollisionDirection::Left) {
					rec.safeLeft = std::max(rec.safeLeft, (x + 1) * TILE_SIZE_F);
				}
				if (rec.collisionDirection == CollisionDirection::Up) {
					rec.safeTop = std::max(rec.safeTop, (y + 1) * TILE_SIZE_F);
				}
				if (rec.collisionDirection == CollisionDirection::Down) {
					rec.safeTop = std::min(rec.safeTop, y * TILE_SIZE_F - bb.height);
				}
				rec.collides = true;
				break; // one collision with the world rec is sufficient? No? Do we have a really fat boss here? if yes, remove the break.
			}
		}
	}

	return rec.collides;
}

void World::calculateCollisionLocations(WorldCollisionQueryRecord& rec, const sf::FloatRect& bb) const {
	if (rec.collisionDirection == CollisionDirection::Right) {
		rec.safeLeft = std::min(rec.safeLeft, bb.left - rec.boundingBox.width);
	}
	if (rec.collisionDirection == CollisionDirection::Left) {
		rec.safeLeft = std::max(rec.safeLeft, bb.left + bb.width);
	}
	if (rec.collisionDirection == CollisionDirection::Up) {
		rec.safeTop = std::max(rec.safeTop, bb.top + bb.height);
	}
	if (rec.collisionDirection == CollisionDirection::Down) {
		rec.safeTop = std::min(rec.safeTop, bb.top - rec.boundingBox.height);
	}
	rec.collides = true;
}

const std::string& World::getID() const {
	return m_worldData->id;
}

const WeatherData& World::getWeather() const {
	return m_worldData->weather;
}

const std::string& World::getMusicPath() const {
	return m_worldData->musicPath;
}

std::string World::getName() const {
	return getNameFromId(m_worldData->id);
}

std::string World::getNameFromId(const std::string id) {
	if (id.size() < 4) return "";
	std::string name = id;
	name = name.substr(0, name.size() - 4);

	std::size_t pos = name.find_last_of('/');
	if (pos == std::string::npos) return "";
	return name.substr(pos + 1);
}

void World::setAmbientDimming(float dimming) const {
	m_worldData->weather.ambientDimming = clamp(dimming, 0.f, 1.f);
}

void World::setLightDimming(float dimming) const {
	m_worldData->weather.lightDimming = clamp(dimming, 0.f, 1.f);
}

bool World::lineBoxIntersection(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::FloatRect& bb, sf::Vector2f& intersection) {
	// check the impossible things
	if (p1.x < bb.left && p2.x < bb.left)
		return false;
	if (p1.x > bb.left + bb.width && p2.x > bb.left + bb.width)
		return false;
	if (p1.y < bb.top && p2.y < bb.top)
		return false;
	if (p1.y > bb.top + bb.height && p2.y > bb.top + bb.height)
		return false;

	// ray direction, no need to normalize
	sf::Vector2f dir = p2 - p1;

	// check the x lines of the box
	bool intersects;
	if (dir.x > 0.f) {
		intersects = lineIntersection(sf::Vector2f(bb.left, bb.top), sf::Vector2f(bb.left, bb.top + bb.height), p1, p2, intersection);
	}
	else {
		intersects = lineIntersection(sf::Vector2f(bb.left + bb.width, bb.top), sf::Vector2f(bb.left + bb.width, bb.top + bb.height), p1, p2, intersection);
	}

	if (intersects) {
		return true;
	}

	// now y
	if (dir.y > 0.f) {
		intersects = lineIntersection(sf::Vector2f(bb.left, bb.top), sf::Vector2f(bb.left + bb.width, bb.top), p1, p2, intersection);
	}
	else {
		intersects = lineIntersection(sf::Vector2f(bb.left, bb.top + bb.height), sf::Vector2f(bb.left + bb.width, bb.top + bb.height), p1, p2, intersection);
	}
	return intersects;
}

bool World::lineIntersection(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2, sf::Vector2f& intersection) {
	sf::Vector2f b = a2 - a1;
	sf::Vector2f d = b2 - b1;
	float bDotDPerp = b.x * d.y - b.y * d.x;

	if (bDotDPerp == 0)
		return false;

	sf::Vector2f c = b1 - a1;
	float t = (c.x * d.y - c.y * d.x) / bDotDPerp;
	if (t < 0 || t > 1)
		return false;

	float u = (c.x * b.y - c.y * b.x) / bDotDPerp;
	if (u < 0 || u > 1)
		return false;

	intersection = a1 + t * b;
	return true;
}