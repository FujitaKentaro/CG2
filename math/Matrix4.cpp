#include "Matrix4.h"

Matrix4::Matrix4() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = 0.0f;
		}
	}

}

// ¬•ª‚ðŽw’è‚µ‚Ä‚Ì¶¬
Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {
	Matrix4 mat = {
		m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = mat.m[i][j];
		}
	}
}

Matrix4& Matrix4::operator*=(const Matrix4& m2) {
	for (int i = 0; i < 4; i++) {
		m[i][0] = m[i][0] * m2.m[0][0] + m[i][1] * m2.m[0][1] + m[i][2] * m2.m[0][2] + m[i][3] * m2.m[0][3];

		m[i][1] = m[i][0] * m2.m[1][0] + m[i][1] * m2.m[1][1] + m[i][2] * m2.m[1][2] + m[i][3] * m2.m[1][3];

		m[i][2] = m[i][0] * m2.m[2][0] + m[i][1] * m2.m[2][1] + m[i][2] * m2.m[2][2] + m[i][3] * m2.m[2][3];

		m[i][3] = m[i][0] * m2.m[3][0] + m[i][1] * m2.m[3][1] + m[i][2] * m2.m[3][2] + m[i][3] * m2.m[3][3];

	}

	return *this;
}