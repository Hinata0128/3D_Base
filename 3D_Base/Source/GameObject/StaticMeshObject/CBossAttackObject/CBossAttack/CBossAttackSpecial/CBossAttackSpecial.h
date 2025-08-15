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
		Preparing,
		Jumping,
		Finished
	};
	SpecialState m_eState;

	D3DXVECTOR3 m_vStartPosition;
	D3DXVECTOR3 m_vTargetPosition;
	D3DXVECTOR3 m_vCurrentPosition;

	float m_fPreparationTimer;

	float m_fProgress;
	const float JUMP_HEIGHT = 5.0f; // ‚±‚ê‚¾‚¯Žc‚·


	bool m_bIsFinished;
};