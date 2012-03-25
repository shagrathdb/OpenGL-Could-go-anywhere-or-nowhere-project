//Taken from WildMagic 5 engine

#ifndef __IMPULSE_LIBMATH_ALGEBRA_IMPVECTOR2_H_
#define __IMPULSE_LIBMATH_ALGEBRA_IMPVECTOR2_H_
#pragma once

#include <vector>
#include <string>
#include <iostream>


/**
 * @class	Vector2
 *
 * @brief	Vector 2. 
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 */

template <typename Real>
class Vector2
{
public:
    // Construction.

    /**
     * @fn	Vector2::Vector2 ();
     *
     * @brief	Default constructor.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     */

    Vector2 ();  // uninitialized

    /**
     * @fn	Vector2::Vector2 (const Vector2& vec);
     *
     * @brief	Copy constructor.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	vec	The vector.
     */

    Vector2 (const Vector2& vec);

    /**
     * @fn	Vector2::Vector2 (const Real x, const Real y);
     *
     * @brief	Constructor.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	x	The x coordinate.
     * @param	y	The y coordinate.
     */

    Vector2 (const Real x, const Real y);

    // Assignment.

    /**
     * @fn	Vector2& Vector2::operator= (const Vector2& vec);
     *
     * @brief	Assignment operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	vec	The vector.
     *
     * @return	A shallow copy of this object.
     */

    Vector2& operator= (const Vector2& vec);

    // Arithmetic operations.

    /**
     * @fn	inline Vector2 Vector2::operator+ (const Vector2& vec) const;
     *
     * @brief	Addition operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	vec	The vector.
     *
     * @return	The result of the operation.
     */

    inline Vector2 operator+ (const Vector2& vec) const;

    /**
     * @fn	inline Vector2 Vector2::operator- (const Vector2& vec) const;
     *
     * @brief	Negation operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	vec	The vector.
     *
     * @return	The result of the operation.
     */

    inline Vector2 operator- (const Vector2& vec) const;

    /**
     * @fn	inline Vector2 Vector2::operator* (Real scalar) const;
     *
     * @brief	Multiplication operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	scalar	The scalar.
     *
     * @return	The result of the operation.
     */

    inline Vector2 operator* (Real scalar) const;

    /**
     * @fn	inline Vector2 Vector2::operator/ (Real scalar) const;
     *
     * @brief	Division operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	scalar	The scalar.
     *
     * @return	The result of the operation.
     */

    inline Vector2 operator/ (Real scalar) const;

    /**
     * @fn	inline Vector2 Vector2::operator- () const;
     *
     * @brief	Subtraction operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @return	The result of the operation.
     */

    inline Vector2 operator- () const;

    // Arithmetic updates.

    /**
     * @fn	inline Vector2& Vector2::operator+= (const Vector2& vec);
     *
     * @brief	Addition assignment operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	vec	The vector.
     *
     * @return	The result of the operation.
     */

    inline Vector2& operator+= (const Vector2& vec);

    /**
     * @fn	inline Vector2& Vector2::operator-= (const Vector2& vec);
     *
     * @brief	Subtraction assignment operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	vec	The vector.
     *
     * @return	The result of the operation.
     */

    inline Vector2& operator-= (const Vector2& vec);

    /**
     * @fn	inline Vector2& Vector2::operator*= (Real scalar);
     *
     * @brief	Multiplication assignment operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	scalar	The scalar.
     *
     * @return	The result of the operation.
     */

    inline Vector2& operator*= (Real scalar);

    /**
     * @fn	inline Vector2& Vector2::operator/= (Real scalar);
     *
     * @brief	Division assignment operator.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	scalar	The scalar.
     *
     * @return	The result of the operation.
     */

    inline Vector2& operator/= (Real scalar);

    // Vector2 operations.

    /**
     * @fn	inline Real Vector2::Length () const;
     *
     * @brief	Gets the length.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @return	.
     */

    inline Real Length () const;

    /**
     * @fn	inline Real Vector2::SquaredLength () const;
     *
     * @brief	Gets the squared length.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @return	.
     */

    inline Real SquaredLength () const;

    /**
     * @fn	inline Real Vector2::Dot (const Vector2& vec) const;
     *
     * @brief	Dots.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	vec	The vector.
     *
     * @return	.
     */

    inline Real Dot (const Vector2& vec) const;

	/**
	 * @fn	static Real Vector2::Dot (const Vector2& vec1, const Vector2& vec2);
	 *
	 * @brief	Dots.
	 *
	 * @author	Noel Waghorn
	 * @date	19/09/2011
	 *
	 * @param	vec1	The first vector.
	 * @param	vec2	The second vector.
	 *
	 * @return	.
	 */

	static Real Dot (const Vector2& vec1, const Vector2& vec2);

    /**
     * @fn	inline Real Vector2::Normalize (const Real epsilon = Math<Real>::ZERO_TOLERANCE);
     *
     * @brief	Normalizes.
     *
     * @author	Noel Waghorn
     * @date	19/09/2011
     *
     * @param	epsilon	(optional) the epsilon.
     *
     * @return	.
     */

    inline Real Normalize (const Real epsilon = Math<Real>::ZERO_TOLERANCE);

	/**
	 * @fn	inline void Vector2::Clear();
	 *
	 * @brief	Clears this object to its blank/initial state.
	 *
	 * @author	Noel Waghorn
	 * @date	19/09/2011
	 */

	inline void Clear();

	// Determines abd returns the Centroid of a Point Cloud

	/**
	 * @fn	inline static Vector2<Real> Vector2::DetermineCentroid(const std::vector<Vector2<Real>>& points);
	 *
	 * @brief	Determine centroid.
	 *
	 * @author	Noel Waghorn
	 * @date	19/09/2011
	 *
	 * @param	points	The points.
	 *
	 * @return	.
	 */

	inline static Vector2<Real> DetermineCentroid(const std::vector<Vector2<Real>>& points);

    // Special vectors.
    ///< The zero
    static const Vector2 ZERO;    // (0,0)
    ///< The unit x coordinate
    static const Vector2 UNIT_X;  // (1,0)
    ///< The unit y coordinate
    static const Vector2 UNIT_Y;  // (0,1)
    ///< The one
    static const Vector2 ONE;     // (1,1)
	///< The gravity
	static const Vector2 GRAVITY; // (0,-9.8)

	///< The x coordinate
	Real x;
	///< The y coordinate
	Real y;
};

// Arithmetic operations.
template <typename Real>
inline Vector2<Real> operator* (Real scalar, const Vector2<Real>& vec);

// Debugging output.
template <typename Real>
std::ostream& operator<< (std::ostream& outFile, const Vector2<Real>& vec);

#include "ImpVector2.inl"

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

#endif
