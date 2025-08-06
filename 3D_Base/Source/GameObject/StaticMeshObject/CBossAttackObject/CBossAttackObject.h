#pragma once
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"

/*************************************************************
*	�{�X�̃I�u�W�F�N�g�N���X.
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