#include "CBoss.h"
#include "Sound/CSoundManager.h"
#include "Collision/BoundingBox/BoundingBox.h"
#include "StaticMash/CStaticMeshManager.h"
#include <windows.h> // GetAsyncKeyState, OutputDebugStringA のため
#include "../../CCharacter/Player/CPlayer.h" // CPlayer の定義をインクルード

CBoss::CBoss()
	: m_TurnSpeed(0.1f)	//きっちりやりたい場合はラジアン値を設定すること.
	, m_MoveSpeed(0.3f)
	, m_MoveState(enMoveState::stop)
	, m_vCurrentMoveVelocity(0.f, 0.f, 0.f)
	, deleta_time(0.f) // 現在不使用
	, m_fSlashCoolTime(SLASH_COOLTIME_DURATION) // 斬撃クールタイムを初期化（開始時は攻撃できないように）
	, m_pPlayer(nullptr) // プレイヤーポインタをnullptrで初期化
{
	AttachMesh(*CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::Enemy));

	// CBossAttackManager を生成
	m_bossAttackManager = std::make_unique<CBossAttackManager>();
}

CBoss::~CBoss()
{
	// unique_ptr は自動で解放されるため、明示的な delete は不要です。
	// m_bossAttackManager はこのデストラクタが呼ばれる際に自動的に解放されます。
}

void CBoss::Update()
{
	float add_value = 0.1f;
	// デルタタイムはゲームループから正確な値を取得することが推奨されますが、ここでは仮の値を設定
	float deltaTime = 1.0f / 60.0f; // 例: 60FPSの場合

	// 攻撃クールタイムカウンタを更新
	m_fSlashCoolTime += deltaTime;

	// --- プレイヤーとボスの距離に基づく攻撃トリガーのメインロジック ---
	// プレイヤーとボス攻撃マネージャーが有効な場合のみ実行
	if (m_pPlayer && m_bossAttackManager)
	{
		D3DXVECTOR3 bossPos = GetPosition(); // ボスの現在の位置
		D3DXVECTOR3 playerPos = m_pPlayer->GetPosition(); // プレイヤーの現在の位置

		// プレイヤーとボスの位置の差ベクトル
		D3DXVECTOR3 diffVec = playerPos - bossPos;

		// 距離の二乗を計算（平方根を取るより高速）
		float distanceSq = D3DXVec3LengthSq(&diffVec);

		// 斬撃攻撃のトリガーとなる距離の閾値の二乗
		const float SLASH_TRIGGER_DISTANCE_SQ = 5.0f * 5.0f; // 例: 5.0f以内

		// クールタイムが経過しており、かつ現在攻撃中でない場合のみ、新しい攻撃を試みる
		if (m_fSlashCoolTime >= SLASH_COOLTIME_DURATION && !m_bossAttackManager->HasActiveAttack())
		{
			// プレイヤーが斬撃攻撃の範囲内にいる場合
			if (distanceSq <= SLASH_TRIGGER_DISTANCE_SQ)
			{
				m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Slash, GetPosition());
				m_fSlashCoolTime = 0.f; // クールタイムをリセット
				OutputDebugStringA("Boss: Player within Slash range, initiating Slash Attack!\n"); // デバッグ出力
			}
			// プレイヤーが斬撃攻撃の範囲外にいる場合、ジャンプ攻撃を試行
			else
			{
				m_bossAttackManager->CreateBossAttack(CBossAttackManager::BossAttackList::Jump, GetPosition());
				m_fSlashCoolTime = 0.f; // クールタイムをリセット
				OutputDebugStringA("Boss: Player outside Slash range, initiating Jump Attack!\n"); // デバッグ出力
			}
		}
	}
	// --- プレイヤーとボスの距離に基づく攻撃トリガーロジックここまで ---

	// ボス攻撃マネージャーの更新ロジック
	if (m_bossAttackManager)
	{
		m_bossAttackManager->Update();

		// アクティブな攻撃があるかチェックし、その位置をボスの位置に適用
		// これにより、ジャンプ攻撃中はボスも一緒にジャンプし、斬撃攻撃中はZ軸に移動します
		CBossAttack* activeAttack = m_bossAttackManager->GetActiveAttack();
		if (activeAttack && activeAttack->IsAttackActive())
		{
			// ボスの位置を攻撃オブジェクトが計算した位置に更新
			SetPosition(activeAttack->GetCalculatedAttackPosition());
		}
	}
	// ボス攻撃マネージャーの更新ロジックここまで

	// X方向のキー入力による移動
	// 攻撃中でない場合のみX方向移動を許可します
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

	UpdateBBox();      // バウンディングボックスの更新
	UpdateBSpherePos(); // バウンディングスフィアの更新

	// ★追加: 地面との衝突処理
	// ボスが地面より下にめり込むのを防ぐため、明示的にY=0.0fを維持
	// ただし、ジャンプ中はCBossAttackJumpがY座標を管理しているので、
	// 攻撃中でない場合にのみ適用するのが望ましいかもしれません。
	// 今回は全ての状況で Y=0.0f 以下にならないようにするシンプルなアプローチです。
	if (m_vPosition.y < 0.0f) {
		SetPosition(m_vPosition.x, 0.0f, m_vPosition.z);
	}

	CCharacter::Update(); // 基底クラスのUpdateも忘れずに呼び出す
}

void CBoss::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CCharacter::Draw(View, Proj, Light, Camera); // 基底クラスの描画処理

	// ボス攻撃マネージャーの描画ロジック
	if (m_bossAttackManager)
	{
		m_bossAttackManager->Draw(View, Proj, Light, Camera);
	}
}

void CBoss::Init()
{
	// ゲーム開始時やリセット時にクールタイムを初期化したい場合
	m_fSlashCoolTime = SLASH_COOLTIME_DURATION; // 最初はクールタイム中で攻撃できない状態に
	// もし CBossAttackManager に Init 関数があればここで呼び出す
	// m_bossAttackManager->Init();
}

void CBoss::InitializeBossPosition(const D3DXVECTOR3& initialPos)
{
	SetPosition(initialPos);
}

void CBoss::RadioControl()
{
	// このメソッドは現在使用されていません。
	// もし移動ロジックをここで行うのであれば、Update()内のX軸移動と重複しないよう注意してください。
}

void CBoss::HandleGroundCollision(CStaticMeshObject* pGroundObject)
{
	// このメソッドは、ジャンプによってY座標を直接0.0fに固定するロジックとは競合する可能性があります。
	// 今回のケースでは、CBossAttackJumpがY座標を管理し、着地時に0.0fに設定するため、
	// ボスが攻撃中でない時の地面との衝突処理としてのみ機能させることが望ましいです。
	// しかし、もし他の地形が存在し、ボスがそれらに乗る必要がある場合は、
	// このメソッドのロジックは重要になります。
	//
	// もし Y=0.0f が唯一の地面であり、ボスが常にその上にいるべきなら、
	// Update()内の `if (m_vPosition.y < 0.0f)` によるクランプの方がシンプルで確実かもしれません。

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