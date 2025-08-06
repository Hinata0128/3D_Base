#pragma once
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"

/*************************************************************
*	ボス攻撃のオブジェクトクラス.
*	ボスの攻撃用基底クラスとなるBossAttackの継承元の仕事をしている.
*	ここでは、基本何も書かない.
*	
*	作成者: 西村 日向.
**/

class CBossAttackObject
	: public CStaticMeshObject
{
public:
	CBossAttackObject();
	virtual ~CBossAttackObject() override;

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

protected:

};