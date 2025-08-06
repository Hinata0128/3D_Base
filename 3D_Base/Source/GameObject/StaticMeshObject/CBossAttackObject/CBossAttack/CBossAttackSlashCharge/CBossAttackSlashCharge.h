#pragma once
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttack.h"

/********************************************************************
* ボスのチャージ攻撃実装.
* 一定時間チャージした後、Z軸方向に突進する攻撃を実装します。
* チャージ中に特定の条件を満たすとX軸に移動する機能も追加します。
**/
class CBossAttackSlashCharge
    : public CBossAttack
{
public:
    CBossAttackSlashCharge();
    ~CBossAttackSlashCharge() override;

    void Update() override;
    void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

    // チャージ攻撃を開始するメソッド
    // Parameters:
    //   bossCurrentPos: 攻撃開始時のボスの現在のワールド座標
    void StartBossSlashCharge(const D3DXVECTOR3& bossCurrentPos);

    // 現在攻撃中であるかを返すメソッド
    // IsSlashingという名称はチャージ攻撃の意図を汲んで変更することも可能です
    bool IsSlashing() const { return m_bIsAttacking; }

    // 攻撃動作中のボスのワールド行列を取得するメソッド
    // ボスの描画や位置更新にこれを使用します
    const D3DXMATRIX& GetAttackWorldMatrix() const { return m_mAttackWorld; }

    // CBossAttackの純粋仮想関数をオーバーライド
    bool IsAttackActive() const override { return m_bIsAttacking; }
    const D3DXVECTOR3& GetCalculatedAttackPosition() const override { return m_vCurrentAttackPos; }

private:
    //
    // 攻撃フェーズ管理用フラグ
    //
    enum class AttackPhase
    {
        None,           // 攻撃待機中
        Charging,       // チャージ中
        Slashing        // 突進中
    };

    AttackPhase m_CurrentPhase; // 現在の攻撃フェーズ

    bool        m_bIsAttacking;           // 攻撃全体がアクティブかどうかを管理するフラグ

    float       m_fCurrentTime;           // 攻撃全体の経過時間 (秒)
    float       m_fChargeDuration;        // チャージの持続時間 (秒)
    float       m_fSlashDuration;         // 突進の持続時間 (秒)

    float       m_fXMoveDistance;         // X軸方向に移動する距離 (今回の要件 - 1.0f)

    D3DXVECTOR3 m_vInitialBossPos;        // 攻撃開始時のボスの初期位置
    D3DXVECTOR3 m_vCurrentAttackPos;      // 攻撃によって計算されるボスの現在位置
    D3DXMATRIX  m_mAttackWorld;           // 攻撃動作中のボスのワールド行列
};