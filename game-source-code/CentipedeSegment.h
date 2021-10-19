#pragma once

#include "GameEntity.h"
#include "SFML/Graphics.hpp"
#include "GameGrid.h"

using Speed_ptr = shared_ptr<float>;

namespace Centipede
{
	enum class YDirection
	{
		Up = 1,
		Down
	};
	enum class XDirection
	{
		Left = 1,
		Right
	};
	enum class Direction
	{
		Up = 1,
		Down,
		Left,
		Right
	};

	static string toString(const YDirection &d)
	{
		switch (d)
		{
		case YDirection::Up:
			return "Y:UP";
		case YDirection::Down:
			return "Y:DOWN";

		default:
			return "";
		}
	}
}

class CentipedeSegment : public GameEntity
{
public:
	CentipedeSegment(const shared_ptr<CentipedeSegment> front, const shared_ptr<CentipedeSegment> back, const Speed_ptr speed);
	void tick(const sf::Time &time);
	void setSpeed(const float &speed);
	const float &getSpeed() const;
	const bool &isHead() const;

	constexpr static const float NORMAL_RANGE = 40.0f;
	constexpr static const float KEYFRAME_INTERVAL = NORMAL_RANGE / 8.0f;

	/**
	 * @brief Used to initalize segment in the chain of segments making the Centipede.
	 *
	 *  Ensures that there is always one head per centipde.
	 *
	 * @param front
	 * @param back
	 */
	void updateChain(const shared_ptr<CentipedeSegment> front, const shared_ptr<CentipedeSegment> back);

private:
	shared_ptr<CentipedeSegment> front_;
	shared_ptr<CentipedeSegment> back_;
	bool isHead_;
	bool isTurning_;
	Centipede::YDirection targetYDir_;
	Centipede::XDirection targetXDir_;
	Centipede::Direction currentDir_;
	const float &manhattanDistance(const shared_ptr<CentipedeSegment> &other) const;
	const bool &headTurning() const;
	Speed_ptr speed_;
	pair<int, int> targetTurnCell_;

	/**
	 * @brief Is called if segment is a head
	 *
	 * @param time
	 */
	void updatePosition(const sf::Time &time);

	/**
	 * @brief Updates each preceding segment recursively, and terminates at the end of the chain.
	 *
	 */
	void updateBack();

	/**
	 * @brief Checks if the movement of the centipede is grid bound, corrects if not
	 *
	 *  The centipede will move within a grid, and will only turn at certain intervals
	 */
	void checkGridBound();

	void updateTurnAnimation(const pair<float, float> &diff);

	void turn(const float &middleX);

	void handleTurn();

	void followFront();

	const sf::Vector2i gridLocate();
};