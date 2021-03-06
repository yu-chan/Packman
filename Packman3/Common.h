#ifndef INCLUDED_COMMON_H
#define INCLUDED_COMMON_H

#define WINDOW_WIDTH  640
#define WINDOW_HALF_WIDTH  WINDOW_WIDTH / 2
#define WINDOW_HEIGHT 480
#define WINDOW_HALF_HEIGHT WINDOW_HEIGHT / 2

// フレームレート
#define FPS 60

// 無敵時間
#define INVINCIBLE_TIME 30

// プレイ中の1マスの幅
#define OBJECT_SIZE 48
#define OBJECT_HALF_SIZE OBJECT_SIZE / 2

// 画像関連
#define IMAGE_OBJECT_ROW 5
#define IMAGE_OBJECT_COL 4
#define ANIMATION_INTERVAL 10

// StaticObjectとCharacterとのコリジョン判定回数
#define STATIC_COLLISION_CNT 4

#endif