#include "CBossAttackManager.h"
#include <windows.h> // OutputDebugStringA のため

CBossAttackManager::CBossAttackManager()
{
}

CBossAttackManager::~CBossAttackManager()
{
    // unique_ptrは自動で解放されるため、明示的な解放処理は通常不要です。
}

void CBossAttackManager::Update()
{
    // アクティブな攻撃があれば更新
    if (m_pAttack)
    {
        m_pAttack->Update();
        // 攻撃が終了したかどうかをチェックし、終了していればunique_ptrをリセット
        if (!m_pAttack->IsAttackActive())
        {
            m_pAttack.reset(); // 攻撃が終了したので解放
            OutputDebugStringA("BossAttackManager: Attack finished and reset.\n");
        }
    }
}

void CBossAttackManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    // アクティブな攻撃があれば描画
    if (m_pAttack)
    {
        m_pAttack->Draw(View, Proj, Light, Camera);
    }
}

// ボスアタックの生成と設定を行う
void CBossAttackManager::CreateBossAttack(BossAttackList attackType, const D3DXVECTOR3& bossCurrentPos)
{
    // 新しい攻撃を生成する前に、現在の攻撃があれば破棄する
    m_pAttack.reset(); // 現在のunique_ptrが保持しているオブジェクトを解放

    switch (attackType)
    {
    case BossAttackList::Slash:
        m_pAttack = std::make_unique<CBossAttackSlash>();
        // 斬撃開始メソッドを呼び出し、ボスの現在位置を渡す
        if (CBossAttackSlash* slash = dynamic_cast<CBossAttackSlash*>(m_pAttack.get()))
        {
            slash->StartBossSlash(bossCurrentPos);
        }
        else
        {
            OutputDebugStringA("Error: Failed to cast to CBossAttackSlash in CreateBossAttack.\n");
        }
        break;

    case BossAttackList::Jump:
        m_pAttack = std::make_unique<CBossAttackJump>();
        if (CBossAttackJump* jump = dynamic_cast<CBossAttackJump*>(m_pAttack.get()))
        {
            jump->StartJump(bossCurrentPos);
        }
        else
        {
            OutputDebugStringA("Error: Failed to cast to CBossAttackJump in CreateBossAttack.\n");
        }
        break;

        // ★追加: チャージ攻撃の生成ロジック
    case BossAttackList::Charge:
        m_pAttack = std::make_unique<CBossAttackSlashCharge>();
        if (CBossAttackSlashCharge* charge = dynamic_cast<CBossAttackSlashCharge*>(m_pAttack.get()))
        {
            charge->StartBossSlashCharge(bossCurrentPos);
        }
        else
        {
            OutputDebugStringA("Error: Failed to cast to CBossAttackSlashCharge in CreateBossAttack.\n");
        }
        break;

    case BossAttackList::max:
        // エラーハンドリングまたは何もしない
        break;
    }
}

void CBossAttackManager::ResetCurrentAttack()
{
    m_pAttack.reset(); // 現在の攻撃を強制的に終了させ、メモリを解放
    OutputDebugStringA("BossAttackManager: Current attack force reset.\n");
}