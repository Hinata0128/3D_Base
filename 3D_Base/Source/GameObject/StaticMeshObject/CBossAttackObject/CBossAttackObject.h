#pragma once
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"

/*************************************************************
*	ボスのオブジェクトクラス.
**/

class CBossAttackObject
	: public CStaticMeshObject
{
public:
	CBossAttackObject();
	virtual ~CBossAttackObject() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

protected:

};