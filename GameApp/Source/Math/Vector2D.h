#pragma once

/**
 * These are 2-dimenional vectors in the plane.
 */
class Vector2D
{
public:
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(const Vector2D& vector);
	virtual ~Vector2D();

	void operator=(const Vector2D& vector);
	void operator+=(const Vector2D& vector);
	void operator-=(const Vector2D& vector);
	Vector2D operator*(double scalar) const;
	Vector2D operator/(double scalar) const;

	double Dot(const Vector2D& vector) const;
	double Cross(const Vector2D& vector) const;
	double Length() const;
	Vector2D Normalized() const;
	Vector2D ProjectedOnto(const Vector2D& unitVector) const;
	Vector2D RejectedFrom(const Vector2D& unitVector) const;
	Vector2D RotatedBy(double rotationAngle) const;
	Vector2D RotatedCCW90() const;
	void Decompose(double& radius, double& angle) const;
	void Compose(double radius, double angle);

public:
	double x;
	double y;
};

Vector2D operator+(const Vector2D& vectorA, const Vector2D& vectorB);
Vector2D operator-(const Vector2D& vectorA, const Vector2D& vectorB);