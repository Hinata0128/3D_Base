#include "CBossAttackShout.h"
#include "..//..//..//CCharacter/Player/CPlayer.h"

CBossAttackShout::CBossAttackShout()
	: m_eState(ShoutState::Finished)
	, m_vBossPos(0.f, 0.f, 0.f)
	, m_vPlayerStartPos(0.f, 0.f, 0.f)
	, m_vKnockbackEndPos(0.f, 0.f, 0.f)
	, m_fShoutTimer(0.f)
	, m_fKnockbackTimer(0.f)
	, m_bIsFinished(true)
	, m_pPlayer(nullptr)
{
}

CBossAttackShout::~CBossAttackShout()
{
}

void CBossAttackShout::StartShoutAttack(const D3DXVECTOR3& bossPos, CPlayer* player)
{
	m_vBossPos = bossPos;
	m_pPlayer = player;
	m_eState = ShoutState::Shouting;
	m_fShoutTimer = 0.f;
	m_bIsFinished = false;

	// ここで叫び声のサウンドを再生
	// CSoundManager::GetInstance()->Play("shout.wav", false);
	OutputDebugStringA("Boss: Shouting initiated!\n");
}

void CBossAttackShout::Update()
{
	if (m_bIsFinished || !m_pPlayer)
	{
		return;
	}

	float deltaTime = 1.0f / 60.0f;

	switch (m_eState)
	{
	case ShoutState::Shouting:
	{
		m_fShoutTimer += deltaTime;
		if (m_fShoutTimer >= SHOUT_DURATION)
		{
			// 叫び声終了。吹き飛ばしを開始する
			m_eState = ShoutState::KnockingBack;
			m_fKnockbackTimer = 0.f;

			// プレイヤーの開始位置と終了位置を計算
			m_vPlayerStartPos = m_pPlayer->GetPosition();
			D3DXVECTOR3 direction = m_vPlayerStartPos - m_vBossPos;
			D3DXVec3Normalize(&direction, &direction);
			direction.y = 0; // 地面に平行な方向
			m_vKnockbackEndPos = m_vPlayerStartPos + direction * 10.0f; // 10.0f は吹き飛ぶ距離
		}
	}
	break;

	case ShoutState::KnockingBack:
	{
		m_fKnockbackTimer += deltaTime;
		float t = m_fKnockbackTimer / KNOCKBACK_DURATION; // 0.0f から 1.0f までの進行度

		if (t >= 1.0f)
		{
			// 吹き飛ばし終了
			m_pPlayer->SetPosition(m_vKnockbackEndPos);
			m_eState = ShoutState::Finished;
			m_bIsFinished = true;
			OutputDebugStringA("Player knockback finished!\n");
		}
		else
		{
			// 放物線の位置を計算
			D3DXVECTOR3 newPos;
			// 水平方向の移動 (線形補間)
			newPos = m_vPlayerStartPos + (m_vKnockbackEndPos - m_vPlayerStartPos) * t;

			// 垂直方向の移動 (放物線)
			float yOffset = KNOCKBACK_HEIGHT * (4.0f * t * (1.0f - t));
			newPos.y += yOffset;

			m_pPlayer->SetPosition(newPos);
		}
	}
	break;

	case ShoutState::Finished:
		// 何もしない
		break;
	}

	CBossAttack::Update();
}

void CBossAttackShout::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	// 叫び声のエフェクト描画など（任意）
	CBossAttack::Draw(View,Proj,Light,Camera);

}

const D3DXVECTOR3& CBossAttackShout::GetCalculatedAttackPosition() const
{
	return m_vBossPos;
}

bool CBossAttackShout::IsAttackActive() const
{
	return !m_bIsFinished;
}