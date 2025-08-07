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
    , m_eCurrentAttackSequenceState(AttackSequenceState::Jump) // 初期攻撃を斬る攻撃に設定
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
        // プレイヤーとの距離計算は、攻撃順序のロジックには使用しない
        // D3DXVECTOR3 bossPos = GetPosition();
        // D3DXVECTOR3 playerPos = m_pPlayer->GetPosition();
        // D3DXVECTOR3 diffVec = playerPos - bossPos;
        // float distance = D3DXVec3Length(&diffVec);

        if (m_fSlashCoolTime >= SLASH_COOLTIME_DURATION && !m_bossAttackManager->HasActiveAttack())
        {
            switch (m_eCurrentAttackSequenceState)
            {
            case AttackSequenceState::Jump:
                m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Jump, GetPosition());
                m_fSlashCoolTime = 0.f;
                m_eCurrentAttackSequenceState = AttackSequenceState::Jump; // 次の攻撃を斬る攻撃に設定（最初に戻る）
                OutputDebugStringA("Boss: Initiating Jump Attack!\n");
                break;
            case AttackSequenceState::Slash:
                m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Slash, GetPosition());
                m_fSlashCoolTime = 0.f;
                m_eCurrentAttackSequenceState = AttackSequenceState::Charge; // 次の攻撃をチャージに設定
                OutputDebugStringA("Boss: Initiating Slash Attack!\n");
                break;

            case AttackSequenceState::Charge:
                m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Charge, GetPosition());
                m_fSlashCoolTime = 0.f;
                m_eCurrentAttackSequenceState = AttackSequenceState::Jump; // 次の攻撃をジャンプに設定
                OutputDebugStringA("Boss: Initiating Charge Attack!\n");
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