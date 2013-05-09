
#pragma once

#include <fixed_point.h>

// Vectormath.h - Defines a vector struct and useful vector functions.

// Using Fixed-Point math here, from the fixed_point library, replacing Double type.
#define double fpml::fixed_point<int, 16>


struct Vector3D
{
	double X;
	double Y;
	double Z;
};



INLINE double GetLengthSquared(Vector3D vector)
{
	return( (vector.X*vector.X) + (vector.Y*vector.Y) + (vector.Z*vector.Z) );
}

INLINE double GetLength(Vector3D vector)
{
	return sqrt(GetLengthSquared(vector));
}

INLINE Vector3D AddVectors2D(Vector3D vector1, Vector3D vector2) //2-dimensional adding of vectors prevents homogenous coordinate Z being altered.
{
	Vector3D out;
	out.X = vector1.X + vector2.X;
	out.Y = vector1.Y + vector2.Y;
	out.Z = vector1.Z;
	return out;
	
}

INLINE Vector3D ScalarMult(Vector3D vector1, double scalar)
{
	Vector3D out;
	
	out.X = vector1.X * scalar;
	out.Y = vector1.Y * scalar;
	out.Z = vector1.Z * scalar;
	
	return out;
}

INLINE Vector3D ScalarDiv(Vector3D vector1, double scalar)
{
	Vector3D out;
	
	out.X = vector1.X / scalar;
	out.Y = vector1.Y / scalar;
	out.Z = vector1.Z / scalar;
	
	return out;
}

INLINE double DotProduct(Vector3D vector1, Vector3D vector2)
{
	return ( (vector1.X*vector2.X) + (vector1.Y*vector2.Y) + (vector1.Z*vector2.Z) );
}

INLINE Vector3D Normal2D(Vector3D in)
{
	// In 2D, the normal of a vector is simple to work out;
	// it's perpendicular.
	
	Vector3D out;
	out.X = -in.Y;
	out.Y = in.X;
	out.Z = in.Z; // for homogenous co-ordinates, the Z axis remains constant.
	return out;
}

INLINE void Normalize(Vector3D &in)
{
	// Normalizing a vector is as simple as dividing it by its length.
	in = ScalarDiv(in, GetLength(in));
	return;	
}

INLINE Vector3D Projection2D(Vector3D projector, Vector3D projectee)
{
	//Projection (in 2D) is useful for figuring out where along a line a point outside the line would be making contact
	// this can be very useful for collision detection.
	
	Vector3D out;
	out.X = ( DotProduct(projector, projectee) / (projectee.X*projectee.X + projectee.Y*projectee.Y) ) * projectee.X;
	out.Y = ( DotProduct(projector, projectee) / (projectee.X*projectee.X + projectee.Y*projectee.Y) ) * projectee.Y;	

	//In 2D, the Z coordinate does not matter.
	out.Z = projector.Z;
	
	return out;
}




