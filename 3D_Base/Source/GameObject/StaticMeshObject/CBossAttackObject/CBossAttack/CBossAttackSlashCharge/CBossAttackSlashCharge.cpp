#include "CBossAttackSlashCharge.h"

CBossAttackSlashCharge::CBossAttackSlashCharge()
    : m_CurrentPhase(AttackPhase::None)
    , m_bIsAttacking(false)
    , m_fCurrentTime(0.0f)
    , m_fChargeDuration(3.0f)          // チャージ時間は3.0秒
    , m_fSlashDuration(2.0f)           // 突進時間は2.0秒
    , m_fXMoveDistance(1.0f)           // X軸方向への移動距離
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
            // チャージ中の位置変化をリセットし、突進開始時の位置を確定
            m_vInitialBossPos = m_vCurrentAttackPos;
            m_fCurrentTime = 0.0f;
        }
        // チャージ中は位置を固定し、移動しない
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

        // 突進中、X軸とZ軸の両方に線形補間を適用して滑らかに移動
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