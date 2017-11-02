#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <random>
#include <time.h>
#include <Windows.h>
using namespace std;

#define PLAYERVELOCITY 3
#define MAX_OBJECTS_COUNT 50
#define MAX_BUILDING_COUNT 50


//enum
//{
//	OBJECT_BUILDING = 0,
//	OBJECT_CHARACTER = 1,
//	OBJECT_BULLET = 2,
//	OBJECT_ARROW = 3
//}OBJECTTYPE;

#define OBJECT_BUILDING 0
#define	OBJECT_CHARACTER  1
#define	OBJECT_BULLET  2
#define	OBJECT_ARROW 3


typedef struct float3
{
	float x;
	float y;
	float z;

}FLOAT3;

typedef struct float4
{
	float x;
	float y;
	float z;
	float a;

}FLOAT4;

typedef struct float4_color
{
	float r;
	float g;
	float b;
	float a;
}FLOAT4_COLOR;



namespace Vector3
{
	inline FLOAT3 Normalize(FLOAT3& vector)
	{
		FLOAT3 vResult;
		vResult.x = vector.x / sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		vResult.y = vector.y / sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		vResult.z = vector.z / sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

		return vResult;
	}
	inline FLOAT3 Add(FLOAT3& vector1, FLOAT3& vector2)
	{
		FLOAT3 vResult;
		vResult.x = vector1.x + vector2.x;
		vResult.y = vector1.y + vector2.y;
		vResult.z = vector1.z + vector2.z;

		return vResult;
	}
	inline FLOAT3 Multiple(FLOAT3& vector1, FLOAT3& vector2)
	{
		FLOAT3 vResult;
		vResult.x = vector1.x * vector2.x;
		vResult.y = vector1.y * vector2.y;
		vResult.z = vector1.z * vector2.z;

		return vResult;
	}
	inline FLOAT3 Multiple(FLOAT3& vector1, float value)
	{
		FLOAT3 vResult;
		vResult.x = vector1.x * value;
		vResult.y = vector1.y * value;
		vResult.z = vector1.z * value;

		return vResult;
	}
	inline float DotProduct(FLOAT3& vector1, FLOAT3& vector2)
	{
		return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
	}
}