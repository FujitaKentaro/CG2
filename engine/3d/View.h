#pragma once
#include "Matrix4.h"
#include "ConvertXM.h"

class View
{
public:
	View();
	~View();
	void Initialize();
	float FieldOfViewY(float focalLengs, float sensor);

public:
	Vector3 eye;
	Vector3 target;
	Vector3 up;

	float focalLengs;
	float camSensor;

	Matrix4 viewMat;
	Matrix4 proMat;

};