#pragma once

#include "Collider.h"

	template <class T>
	class BoxCollider : public Collider<T>
	{
	private:

		Vec2 _size;

	public:

		/// <summary>
		/// Constructor for creating a BoxCollider.
		/// </summary>
		/// <param name="owner">The owner of the collider</param>
		/// <param name="nextPosition">The position of the collider</param>
		/// <param name="size">The size of the box</param>
		/// <param name="isStatic">Whether the collider is static or not (default is false)</param>
		BoxCollider(T* owner, Vec2 nextPosition, Vec2 size, bool isStatic = false);

		/// <summary>
		/// Updates the position of the collider to the given position.
		/// </summary>
		/// <param name="nextPosition">The position to update to</param>
		void UpdatePosition(Vec2 nextPosition) override;

		/// <summary>
		/// Gets the center point of the collider.
		/// </summary>
		/// <returns>The center point of the collider</returns>
		Vec2 GetCenter() override;

		/// <summary>
		/// Gets the width of the collider.
		/// </summary>
		/// <returns>The width of the collider</returns>
		float GetWidth();

		/// <summary>
		/// Gets the height of the collider.
		/// </summary>
		/// <returns>The height of the collider</returns>
		float GetHeight();

		/// <summary>
		/// Gets the number of points that define the collider's shape in world space.
		/// </summary>
		/// <returns>The number of points that define the collider's shape in world space</returns>
		int GetNumPoints();

		/// <summary>
		/// Gets a vector of the points that define the collider's shape in world space.
		/// </summary>
		/// <returns>A vector of the points that define the collider's shape in world space</returns>
		std::vector<Vec2> GetWorldPoints();
	};

	template<class T>
	BoxCollider<T>::BoxCollider(T* owner, Vec2 nextPosition, Vec2 size, bool isStatic) : Collider<T>(owner, nextPosition, isStatic)
	{
		_size = size;
		UpdatePosition(nextPosition);
	}

	template<class T>
	void BoxCollider<T>::UpdatePosition(Vec2 nextPosition)
	{
		_position = nextPosition;
	}

	template<class T>
	Vec2 BoxCollider<T>::GetCenter()
	{
		return Vec2(_position.GetX() + GetWidth() / 2, _position.GetY() + GetHeight() / 2);
	}

	template<class T>
	float BoxCollider<T>::GetWidth()
	{
		_size.GetX();
	}

	template<class T>
	float BoxCollider<T>::GetHeight()
	{
		_size.GetY();
	}

	template<class T>
	int BoxCollider<T>::GetNumPoints()
	{
		return GetWorldPoints().size();
	}

	template<class T>
	std::vector<Vec2> BoxCollider<T>::GetWorldPoints()
	{
		std::vector<Vec2> points;
		points.push_back(Vec2(_position.GetX(), _position.GetY()));
		points.push_back(Vec2(_position.GetX() + GetWidth(), _position.GetY()));
		points.push_back(Vec2(_position.GetX() + GetWidth(), _position.GetY() + GetHeight()));
		points.push_back(Vec2(_position.GetX(), _position.GetY() + GetHeight()));
		return points;
	}