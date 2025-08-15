#pragma once
#include "..//CBossAttack.h"

class CBossAttackSpecial
	: public CBossAttack
{
public:
	CBossAttackSpecial();
	~CBossAttackSpecial() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void StartSpecialAttack(const D3DXVECTOR3& startPos, const D3DXVECTOR3& targetPos);

	const D3DXVECTOR3& GetCalculatedAttackPosition() const override;
	bool IsAttackActive() const override;

private:
	enum class SpecialState
	{
		Jumping,   // ジャンプと突進を統合
		Finished
	};
	SpecialState m_eState;

	D3DXVECTOR3 m_vStartPosition;
	D3DXVECTOR3 m_vTargetPosition;
	D3DXVECTOR3 m_vCurrentPosition;

	float m_fProgress;
	const float ATTACK_DURATION = 2.0f; // 攻撃全体にかかる時間
	const float JUMP_HEIGHT = 8.0f;

	bool m_bIsFinished;
};