#include "CBossAttackSlashCharge.h"

CBossAttackSlashCharge::CBossAttackSlashCharge()
    : m_CurrentPhase(AttackPhase::None)
    , m_bIsAttacking(false)
    , m_fCurrentTime(0.0f)
    , m_fChargeDuration(3.0f)          // �`���[�W���Ԃ�3.0�b
    , m_fSlashDuration(2.0f)           // �ːi���Ԃ�2.0�b
    , m_fXMoveDistance(1.0f)           // X�������ւ̈ړ�����
    , m_vInitialBossPos(0.0f, 0.0f, 0.0f)
    , m_vCurrentAttackPos(0.0f, 0.0f, 0.0f)
{
    D3DXMatrixIdentity(&m_mAttackWorld);
}

CBossAttackSlashCharge::~CBossAttackSlashCharge()
{
}

void CBossAttackSlashCharge::StartBossSlashCharge(const D3DXVECTOR3& bossCurrentPos)
{
    if (m_bIsAttacking)
    {
        return;
    }

    m_bIsAttacking = true;
    m_CurrentPhase = AttackPhase::Charging;
    m_fCurrentTime = 0.0f;
    m_vInitialBossPos = bossCurrentPos;
    m_vCurrentAttackPos = bossCurrentPos;
}

void CBossAttackSlashCharge::Update()
{
    if (!m_bIsAttacking)
    {
        return;
    }

    float deltaTime = 1.0f / 60.0f;
    m_fCurrentTime += deltaTime;

    switch (m_CurrentPhase)
    {
    case AttackPhase::Charging:
    {
        if (m_fCurrentTime >= m_fChargeDuration)
        {
            m_CurrentPhase = AttackPhase::Slashing;
            // �`���[�W���̈ʒu�ω������Z�b�g���A�ːi�J�n���̈ʒu���m��
            m_vInitialBossPos = m_vCurrentAttackPos;
            m_fCurrentTime = 0.0f;
        }
        // �`���[�W���͈ʒu���Œ肵�A�ړ����Ȃ�
        break;
    }

    case AttackPhase::Slashing:
    {
        if (m_fCurrentTime >= m_fSlashDuration)
        {
            m_bIsAttacking = false;
            m_CurrentPhase = AttackPhase::None;
            m_fCurrentTime = m_fSlashDuration;
            break;
        }

        float progress = m_fCurrentTime / m_fSlashDuration;
        if (progress > 1.0f)
        {
            progress = 1.0f;
        }

        // �ːi���AX����Z���̗����ɐ��`��Ԃ�K�p���Ċ��炩�Ɉړ�
        m_vCurrentAttackPos.x = m_vInitialBossPos.x + (m_fXMoveDistance * progress);
        m_vCurrentAttackPos.y = m_vInitialBossPos.y;
        m_vCurrentAttackPos.z = m_vInitialBossPos.z;

        break;
    }

    default:
        break;
    }

    SetPosition(m_vCurrentAttackPos);
    CStaticMeshObject::Update();
}

void CBossAttackSlashCharge::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    if (m_bIsAttacking)
    {
        CStaticMeshObject::Draw(View, Proj, Light, Camera);
    }
}