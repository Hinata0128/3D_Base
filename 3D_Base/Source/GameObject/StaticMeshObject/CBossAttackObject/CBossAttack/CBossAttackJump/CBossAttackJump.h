#pragma once

#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttack.h"

class CBossAttackJump
    : public CBossAttack
{
public:
    CBossAttackJump();
    ~CBossAttackJump() override;

    void Update() override;
    void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

    void StartJump(const D3DXVECTOR3& bossCurrentPos);

    bool IsAttackActive() const override { return m_bIsJumping; }
    const D3DXVECTOR3& GetCalculatedAttackPosition() const override { return m_vCurrentAttackPos; }

private:
    bool m_bIsJumping;             // ジャンプ中かどうかを管理するフラグ
    float m_fCurrentJumpTime;      // 現在のジャンプ経過時間 (秒)
    float m_fJumpDuration;         // ジャンプの持続時間 (秒) - このモデルでは直接使わないが、目安として残す
    float m_fJumpHeight;           // ジャンプの最大高さ - このモデルでは直接使わないが、目安として残す

    // ★追加・変更: 物理ジャンプに必要な変数
    D3DXVECTOR3 m_vInitialBossPos; // ジャンプ開始時のボスの初期位置 (X, Zは維持、Yはジャンプ前の地面のYを保持)
    D3DXVECTOR3 m_vCurrentAttackPos; // ジャンプ中のボスの現在位置 (このクラスで計算される位置)

    D3DXVECTOR3 m_vJumpVelocity;   // ジャンプ中の現在のY方向速度
    float       m_JumpPower;       // ジャンプの初速度（プレイヤーのm_JumpPowerに相当）
    float       m_Gravity;         // 重力加速度（プレイヤーのm_Gravityに相当）
    // bool        m_GroundedFlag; // ボス攻撃側では外部（CBoss）が管理するので不要
};