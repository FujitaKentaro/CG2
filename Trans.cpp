#include "Trans.h"

Trans::Trans() {
	// ���[�J���X�P�[��
	scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	rotation = { 0,0,0 };
	// ���[�J�����W
	position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	matWorld = Affin::matUnit();
}
Trans::~Trans() {}

void Trans::Initialize() {
	// ���[�J���X�P�[��
	scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	rotation = { 0,0,0 };
	// ���[�J�����W
	position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	matWorld = Affin::matUnit();
}