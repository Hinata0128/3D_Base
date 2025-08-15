#include "CBoss.h"
#include "Sound/CSoundManager.h"
#include "Collision/BoundingBox/BoundingBox.h"
#include "StaticMash/CStaticMeshManager.h"
#include <windows.h>
#include "../../CCharacter/Player/CPlayer.h"

CBoss::CBoss()
    : m_TurnSpeed(0.1f)
    , m_MoveSpeed(0.3f)
    , m_MoveState(enMoveState::stop)
    , m_vCurrentMoveVelocity(0.f, 0.f, 0.f)
    , deleta_time(0.f)
    , m_fSlashCoolTime(SLASH_COOLTIME_DURATION)
    , m_pPlayer(nullptr)
    , m_eCurrentAttackSequenceState(AttackSequenceState::Jump) // 初期攻撃をジャンプ攻撃に設定
{
    AttachMesh(*CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::Enemy));
    m_bossAttackManager = std::make_unique<CBossAttackManager>();
}

CBoss::~CBoss()
{
}

void CBoss::Update()
{
    float add_value = 0.1f;
    float deltaTime = 1.0f / 60.0f;

    m_fSlashCoolTime += deltaTime;

    if (m_pPlayer && m_bossAttackManager)
    {
        if (m_fSlashCoolTime >= SLASH_COOLTIME_DURATION && !m_bossAttackManager->HasActiveAttack())
        {
            // プレイヤーの位置を取得
            D3DXVECTOR3 playerPos = m_pPlayer->GetPosition();

            switch (m_eCurrentAttackSequenceState)
            {
            case AttackSequenceState::Jump:
                // CreateBossAttackの引数を修正
                m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Jump, GetPosition(), playerPos);
                m_fSlashCoolTime = 0.f;
                m_eCurrentAttackSequenceState = AttackSequenceState::Slash;
                OutputDebugStringA("Boss: Initiating Jump Attack!\n");
                break;

            case AttackSequenceState::Slash:
                // CreateBossAttackの引数を修正
                m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Slash, GetPosition(), playerPos);
                m_fSlashCoolTime = 0.f;
                m_eCurrentAttackSequenceState = AttackSequenceState::Charge;
                OutputDebugStringA("Boss: Initiating Slash Attack!\n");
                break;

            case AttackSequenceState::Charge:
                // CreateBossAttackの引数を修正
                m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Charge, GetPosition(), playerPos);
                m_fSlashCoolTime = 0.f;
                m_eCurrentAttackSequenceState = AttackSequenceState::Special; // 次の攻撃をスペシャルに設定
                OutputDebugStringA("Boss: Initiating Charge Attack!\n");
                break;

                // ★追加: スペシャル攻撃のロジック
            case AttackSequenceState::Special:
                // プレイヤーの位置を取得して、CreateBossAttackに渡す
                m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Special, GetPosition(), playerPos);
                m_fSlashCoolTime = 0.f;
                m_eCurrentAttackSequenceState = AttackSequenceState::Jump; // 攻撃シーケンスを最初に戻す
                OutputDebugStringA("Boss: Initiating Special Attack!\n");
                break;

            default:
                break;
            }
        }
    }

    if (m_bossAttackManager)
    {
        m_bossAttackManager->Update();

        CBossAttack* activeAttack = m_bossAttackManager->GetActiveAttack();
        if (activeAttack && activeAttack->IsAttackActive())
        {
            // 攻撃の位置にボスの位置を同期
            SetPosition(activeAttack->GetCalculatedAttackPosition());
        }
    }

    if (!m_bossAttackManager->HasActiveAttack())
    {
        m_vCurrentMoveVelocity.x = 0.f;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            m_vCurrentMoveVelocity.x = -add_value;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            m_vCurrentMoveVelocity.x = add_value;
        }
        m_vPosition.x += m_vCurrentMoveVelocity.x;
    }

    UpdateBBox();
    UpdateBSpherePos();

    if (m_vPosition.y < 0.0f) {
        SetPosition(m_vPosition.x, 0.0f, m_vPosition.z);
    }

    CCharacter::Update();
}

void CBoss::Draw(
    D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    CCharacter::Draw(View, Proj, Light, Camera);

    if (m_bossAttackManager)
    {
        m_bossAttackManager->Draw(View, Proj, Light, Camera);
    }
}

void CBoss::Init()
{
    m_fSlashCoolTime = SLASH_COOLTIME_DURATION;
}

void CBoss::InitializeBossPosition(const D3DXVECTOR3& initialPos)
{
    SetPosition(initialPos);
}

void CBoss::RadioControl()
{
}

void CBoss::HandleGroundCollision(CStaticMeshObject* pGroundObject)
{
    BoundingBox* BossBBox = this->GetBBox();
    BoundingBox* groundBBox = pGroundObject->GetBBox();

    if (BossBBox == nullptr || groundBBox == nullptr) {
        return;
    }

    if (BossBBox->GetMinPosition().y < groundBBox->GetMaxPosition().y) {
        float bossHalfHeight = (BossBBox->GetMaxPosition().y - BossBBox->GetMinPosition().y) / 2.0f;
        this->SetPosition(m_vPosition.x, groundBBox->GetMaxPosition().y + bossHalfHeight, m_vPosition.z);
    }
}