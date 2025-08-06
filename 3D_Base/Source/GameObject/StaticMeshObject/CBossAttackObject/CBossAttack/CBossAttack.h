#pragma once
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttackObject.h"

/******************************************************
*	ボスの攻撃基底クラス.
**/

class CBossAttack
	: public CBossAttackObject
{
public:
	CBossAttack();
	virtual ~CBossAttack() override;

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	// ★追加: 攻撃が計算したワールド位置を取得する純粋仮想関数
	virtual const D3DXVECTOR3& GetCalculatedAttackPosition() const = 0;
	// ★追加: 攻撃が現在アクティブかどうかを返す純粋仮想関数
	virtual bool IsAttackActive() const = 0;

protected:

};