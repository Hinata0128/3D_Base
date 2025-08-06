#include "CBossAttackSlash.h"
#include <iostream> // デバッグ出力用（必要なければ削除）
#include <windows.h> // OutputDebugStringA のため

CBossAttackSlash::CBossAttackSlash()
    : m_bIsSlashing(false)
    , m_fCurrentSlashTime(0.0f)
    , m_fSlashDuration(0.5f)       // 斬撃の持続時間を0.5秒に設定 (調整可能)
    , m_fZMoveDistance(-2.0f)      // Z軸方向に-2だけ進む (調整可能) 現状アニメーションがないため肉眼で確認できるコードにしている
    , m_vInitialBossPos(0.0f, 0.0f, 0.0f)
    , m_vCurrentAttackPos(0.0f, 0.0f, 0.0f)
{
    D3DXMatrixIdentity(&m_mAttackWorld); // ワールド行列を単位行列で初期化
}

CBossAttackSlash::~CBossAttackSlash()
{
}

// 斬撃攻撃を開始する
void CBossAttackSlash::StartBossSlash(const D3DXVECTOR3& bossCurrentPos)
{
    if (m_bIsSlashing) return; // 既に斬撃中なら何もしない

    m_bIsSlashing = true;
    m_fCurrentSlashTime = 0.0f; // 経過時間をリセット
    m_vInitialBossPos = bossCurrentPos; // 攻撃開始時のボスの位置を保存
    m_vCurrentAttackPos = bossCurrentPos; // 現在位置も初期位置で初期化

    OutputDebugStringA("Slash Started!\n"); // デバッグウィンドウに出力
}

// 斬撃攻撃の更新
void CBossAttackSlash::Update()
{
    if (!m_bIsSlashing) return; // 斬撃中でなければ何もしない

    // デルタタイムの取得（実際のゲームループから正確な値を取得してください）
    // 仮に60FPS固定と仮定 (1.0f / 60.0f = 約0.01666f)
    float deltaTime = 1.0f / 60.0f;

    m_fCurrentSlashTime += deltaTime;

    // 斬撃が終了時間になったら停止
    if (m_fCurrentSlashTime >= m_fSlashDuration)
    {
        m_bIsSlashing = false;
        m_fCurrentSlashTime = m_fSlashDuration; // 最終フレームでの計算のため、時間をクランプ
        OutputDebugStringA("Slash Ended.\n"); // デバッグウィンドウに出力
        // 攻撃終了時にオブジェクトを非アクティブにするなどの処理が必要な場合、ここに追加
    }

    // 線形補間を使ってZ軸方向に移動
    // 進行度 (0.0f から 1.0f)。時間が経過するにつれて0から1へ変化
    float progress = m_fCurrentSlashTime / m_fSlashDuration;
    if (progress > 1.0f) progress = 1.0f; // 1.0f を超えないようにクランプ

    // Z軸方向への移動量を計算
    float currentZMove = m_fZMoveDistance * progress;

    // 攻撃によって計算されるボスの現在位置
    m_vCurrentAttackPos.x = m_vInitialBossPos.x; // X座標は変更しない
    m_vCurrentAttackPos.y = m_vInitialBossPos.y; // Y座標は変更しない
    m_vCurrentAttackPos.z = m_vInitialBossPos.z + currentZMove; // Z座標のみ変化

    // CStaticMeshObjectの内部位置を更新
    SetPosition(m_vCurrentAttackPos);

    CStaticMeshObject::Update(); // 基底クラスのUpdateを呼び出す (ワールド行列の更新など)
}

void CBossAttackSlash::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    if (m_bIsSlashing)
    {
        // 攻撃オブジェクト自身の描画処理
        CStaticMeshObject::Draw(View, Proj, Light, Camera); // 基底クラスの描画を呼び出す
    }
}