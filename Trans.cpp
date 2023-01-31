#include "Trans.h"

Trans::Trans() {
	// ローカルスケール
	scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	rotation = { 0,0,0 };
	// ローカル座標
	position = { 0,0,0 };
	// ローカルワールド変換行列
	matWorld = Affin::matUnit();
}
Trans::~Trans() {}

void Trans::Initialize() {
	// ローカルスケール
	scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	rotation = { 0,0,0 };
	// ローカル座標
	position = { 0,0,0 };
	// ローカルワールド変換行列
	matWorld = Affin::matUnit();
}