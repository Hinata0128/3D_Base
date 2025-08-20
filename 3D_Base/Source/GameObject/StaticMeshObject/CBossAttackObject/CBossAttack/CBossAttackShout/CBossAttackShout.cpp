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

	// �����ŋ��ѐ��̃T�E���h���Đ�
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
			// ���ѐ��I���B������΂����J�n����
			m_eState = ShoutState::KnockingBack;
			m_fKnockbackTimer = 0.f;

			// �v���C���[�̊J�n�ʒu�ƏI���ʒu���v�Z
			m_vPlayerStartPos = m_pPlayer->GetPosition();
			D3DXVECTOR3 direction = m_vPlayerStartPos - m_vBossPos;
			D3DXVec3Normalize(&direction, &direction);
			direction.y = 0; // �n�ʂɕ��s�ȕ���
			m_vKnockbackEndPos = m_vPlayerStartPos + direction * 10.0f; // 10.0f �͐�����ԋ���
		}
	}
	break;

	case ShoutState::KnockingBack:
	{
		m_fKnockbackTimer += deltaTime;
		float t = m_fKnockbackTimer / KNOCKBACK_DURATION; // 0.0f ���� 1.0f �܂ł̐i�s�x

		if (t >= 1.0f)
		{
			// ������΂��I��
			m_pPlayer->SetPosition(m_vKnockbackEndPos);
			m_eState = ShoutState::Finished;
			m_bIsFinished = true;
			OutputDebugStringA("Player knockback finished!\n");
		}
		else
		{
			// �������̈ʒu���v�Z
			D3DXVECTOR3 newPos;
			// ���������̈ړ� (���`���)
			newPos = m_vPlayerStartPos + (m_vKnockbackEndPos - m_vPlayerStartPos) * t;

			// ���������̈ړ� (������)
			float yOffset = KNOCKBACK_HEIGHT * (4.0f * t * (1.0f - t));
			newPos.y += yOffset;

			m_pPlayer->SetPosition(newPos);
		}
	}
	break;

	case ShoutState::Finished:
		// �������Ȃ�
		break;
	}

	CBossAttack::Update();
}

void CBossAttackShout::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	// ���ѐ��̃G�t�F�N�g�`��Ȃǁi�C�Ӂj
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