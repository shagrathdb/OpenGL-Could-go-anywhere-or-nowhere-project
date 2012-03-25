//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> Vector2<Real>::Vector2 ()
 *
 * @brief	Gets the vector 2.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 *
 * @return	.
 */

template <typename Real>
Vector2<Real>::Vector2 ()
{
    // Uninitialized for performance in array construction.
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> Vector2<Real>::Vector2 (const Vector2& vec)
 *
 * @brief	Vector 2.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	vec	The vector.
 *
 * @return	.
 */

template <typename Real>
Vector2<Real>::Vector2 (const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> Vector2<Real>::Vector2 (const Real x, const Real y)
 *
 * @brief	Vector 2.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 *
 * @return	.
 */

template <typename Real>
Vector2<Real>::Vector2 (const Real x, const Real y)
{
    this->x = x;
    this->y = y;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real>& Vector2<Real>::operator= (const Vector2& vec)
 *
 * @brief	= casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	vec	The vector.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real>& Vector2<Real>::operator= (const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
    return *this;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real> Vector2<Real>::operator+ (const Vector2& vec) const
 *
 * @brief	+ casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	vec	The vector.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real> Vector2<Real>::operator+ (const Vector2& vec) const
{
    return Vector2
    (
        x + vec.x,
        y + vec.y
    );
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real> Vector2<Real>::operator- (const Vector2& vec) const
 *
 * @brief	- casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	vec	The vector.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real> Vector2<Real>::operator- (const Vector2& vec) const
{
    return Vector2
    (
        x - vec.x,
        y - vec.y
    );
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real> Vector2<Real>::operator* (Real scalar) const
 *
 * @brief	* casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	scalar	The scalar.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real> Vector2<Real>::operator* (Real scalar) const
{
    return Vector2
    (
        scalar*x,
        scalar*y
    );
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real> Vector2<Real>::operator/ (Real scalar) const
 *
 * @brief	/ casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	scalar	The scalar.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real> Vector2<Real>::operator/ (Real scalar) const
{
    Vector2 result;

    if (scalar != (Real)0)
    {
        Real invScalar = ((Real)1)/scalar;
        result.x = invScalar*x;
        result.y = invScalar*y;
    }
    else
    {
        result.x = Math<Real>::MAX_REAL;
        result.y = Math<Real>::MAX_REAL;
    }

    return result;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real> Vector2<Real>::operator- () const
 *
 * @brief	- casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real> Vector2<Real>::operator- () const
{
    return Vector2
    (
        -x,
        -y
    );
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real>& Vector2<Real>::operator+= (const Vector2& vec)
 *
 * @brief	+= casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	vec	The vector.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real>& Vector2<Real>::operator+= (const Vector2& vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real>& Vector2<Real>::operator-= (const Vector2& vec)
 *
 * @brief	-= casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	vec	The vector.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real>& Vector2<Real>::operator-= (const Vector2& vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real>& Vector2<Real>::operator*= (Real scalar)
 *
 * @brief	*= casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	scalar	The scalar.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real>& Vector2<Real>::operator*= (Real scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real>& Vector2<Real>::operator/= (Real scalar)
 *
 * @brief	/= casting operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	scalar	The scalar.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real>& Vector2<Real>::operator/= (Real scalar)
{
    if (scalar != (Real)0)
    {
        Real invScalar = ((Real)1)/scalar;
        x *= invScalar;
        y *= invScalar;
    }
    else
    {
        x *= Math<Real>::MAX_REAL;
        y *= Math<Real>::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Real Vector2<Real>::Length () const
 *
 * @brief	Gets the length.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 *
 * @return	.
 */

template <typename Real>
inline Real Vector2<Real>::Length () const
{
    return Math<Real>::Sqrt
    (
        x*x +
        y*y
    );
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Real Vector2<Real>::SquaredLength () const
 *
 * @brief	Gets the squared length.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 *
 * @return	.
 */

template <typename Real>
inline Real Vector2<Real>::SquaredLength () const
{
    return
        x*x +
        y*y;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Real Vector2<Real>::Dot (const Vector2& vec) const
 *
 * @brief	Dots.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	vec	The vector.
 *
 * @return	.
 */

template <typename Real>
inline Real Vector2<Real>::Dot (const Vector2& vec) const
{
    return
        x*vec.x +
        y*vec.y;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Real Vector2<Real>::Dot(const Vector2& vec1,
 * 		const Vector2& vec2)
 *
 * @brief	Dots.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	vec1	The first vector.
 * @param	vec2	The second vector.
 *
 * @return	.
 */

template <typename Real>
inline Real Vector2<Real>::Dot(const Vector2& vec1, const Vector2& vec2)
{
	return
        vec1.x*vec2.x +
        vec1.y*vec2.y;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Real Vector2<Real>::Normalize (const Real epsilon)
 *
 * @brief	Normalizes.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	epsilon	The epsilon.
 *
 * @return	.
 */

template <typename Real>
inline Real Vector2<Real>::Normalize (const Real epsilon)
{
    Real length = Length();

    if (length > epsilon)
    {
        Real invLength = ((Real)1)/length;
        x *= invLength;
        y *= invLength;
    }
    else
    {
        length = (Real)0;
        x = (Real)0;
        y = (Real)0;
    }

    return length;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline void Vector2<Real>::Clear()
 *
 * @brief	Clears this object to its blank/initial state.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 */

template <typename Real>
inline void Vector2<Real>::Clear()
{
	x = 0;
	y = 0;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real> Vector2<Real>::DetermineCentroid(const std::vector<Vector2<Real>>& points)
 *
 * @brief	Determine centroid.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @tparam	Real	Type of the real.
 * @param	points	The points.
 *
 * @return	.
 */

template <typename Real>
inline Vector2<Real> Vector2<Real>::DetermineCentroid(const std::vector<Vector2<Real>>& points)
{
	// The scalar multiplier to be applied to the centroid = 1 / n
	Real scalar = 1 / (Real)points.size();
	Vector2<Real> centroid(Vector2<Real>::ZERO);

	// Determine the centroid of the point cloud ( centroid = scalar * SUM of POSITION VECTORS OF POINTS)
	for(int i = 0; i < (int)points.size(); i++)
	{
		centroid += points[i];
	}

	centroid *= scalar;

	return centroid;
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> inline Vector2<Real> operator* (Real scalar,
 * 		const Vector2<Real>& vec)
 *
 * @brief	Multiplication operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @param	scalar	The first value to multiply.
 * @param	vec   	The second value to multiply.
 *
 * @return	The result of the operation.
 */

template <typename Real>
inline Vector2<Real> operator* (Real scalar, const Vector2<Real>& vec)
{
    return Vector2<Real>
    (
        scalar*x,
        scalar*y
    );
}
//----------------------------------------------------------------------------

/**
 * @fn	template <typename Real> std::ostream& operator<< (std::ostream& outFile, const Vector2<Real>& vec)
 *
 * @brief	Bitwise left shift operator.
 *
 * @author	Noel Waghorn
 * @date	19/09/2011
 *
 * @param [in,out]	outFile	The out file.
 * @param	vec			   	The vector.
 *
 * @return	The shifted result.
 */

template <typename Real>
std::ostream& operator<< (std::ostream& outFile, const Vector2<Real>& vec)
{
	return outFile << vec.X() << ' ' << vec.Y();
}
//----------------------------------------------------------------------------