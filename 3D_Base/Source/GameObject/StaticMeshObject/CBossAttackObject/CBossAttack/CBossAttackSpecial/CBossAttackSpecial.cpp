#include "CBossAttackSpecial.h"

// 攻撃全体にかかる時間。この値を調整して速度を変えます。
const float ATTACK_DURATION = 2.0f;
const float JUMP_HEIGHT = 8.0f;

CBossAttackSpecial::CBossAttackSpecial()
	: m_eState(SpecialState::Jumping)
	, m_vStartPosition(0.0f, 0.0f, 0.0f)
	, m_vTargetPosition(0.0f, 0.0f, 0.0f)
	, m_vCurrentPosition(0.0f, 0.0f, 0.0f)
	, m_fProgress(0.0f)
	, m_bIsFinished(true)
{
}

CBossAttackSpecial::~CBossAttackSpecial()
{
}

void CBossAttackSpecial::StartSpecialAttack(const D3DXVECTOR3& startPos, const D3DXVECTOR3& targetPos)
{
	m_vStartPosition = startPos;
	m_vTargetPosition = targetPos;
	m_vCurrentPosition = startPos;
	m_fProgress = 0.0f;
	m_eState = SpecialState::Jumping;
	m_bIsFinished = false;
}

void CBossAttackSpecial::Update()
{
	if (m_bIsFinished)
	{
		return;
	}

	float deltaTime = 1.0f / 60.0f;

	switch (m_eState)
	{
	case SpecialState::Jumping:
	{
		m_fProgress += deltaTime / ATTACK_DURATION;
		if (m_fProgress <= 1.0f)
		{
			// ジャンプから着地までを一つの放物線運動として計算
			D3DXVECTOR3 horizontalPos = m_vStartPosition + (m_vTargetPosition - m_vStartPosition) * m_fProgress;
			float y = JUMP_HEIGHT * (4.0f * m_fProgress * (1.0f - m_fProgress));
			m_vCurrentPosition = D3DXVECTOR3(horizontalPos.x, m_vStartPosition.y + y, horizontalPos.z);
		}
		else
		{
			m_vCurrentPosition = m_vTargetPosition;
			m_eState = SpecialState::Finished;
			m_bIsFinished = true;
		}
	}
	break;

	case SpecialState::Finished:
		break;
	}

	SetPosition(m_vCurrentPosition);
	CBossAttack::Update();
}

void CBossAttackSpecial::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CBossAttack::Draw(View, Proj, Light, Camera);
}

const D3DXVECTOR3& CBossAttackSpecial::GetCalculatedAttackPosition() const
{
	return m_vCurrentPosition;
}

bool CBossAttackSpecial::IsAttackActive() const
{
	return !m_bIsFinished;
}