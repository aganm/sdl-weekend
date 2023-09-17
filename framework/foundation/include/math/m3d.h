#ifndef M3D_H
#define M3D_H

/**
 * @file
 * @brief 3D math library.
 */

#include <types/bundle.h>
#include <types/primitive.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "math_helpers.h"
#include <math.h>

static inline f32m4x4 m3dLookat(f32v3 camera, f32v3 target, f32v3 up_axis)
{
	f32v3 forward;
	forward.x = target.x - camera.x;
	forward.y = target.y - camera.y;
	forward.z = target.z - camera.z;

	float length = f32v3_length(forward);
	if (length == 0.f) length = 0.0001f;
	forward.x /= length;
	forward.y /= length;
	forward.z /= length;

	f32v3 right;
	right.x = forward.y * up_axis.z - forward.z * up_axis.y;
	right.y = forward.z * up_axis.x - forward.x * up_axis.z;
	right.z = forward.x * up_axis.y - forward.y * up_axis.x;

	length = f32v3_length(right);
	if (length == 0.f) length = 0.0001f;
	right.x /= length;
	right.y /= length;
	right.z /= length;

	f32v3 up;
	up.x = right.y * forward.z - right.z * forward.y;
	up.y = right.z * forward.x - right.x * forward.z;
	up.z = right.x * forward.y - right.y * forward.x;

	f32m4x4 view;
	view.raw[0] = right.x;
	view.raw[1] = up.x;
	view.raw[2] = -forward.x;
	view.raw[3] = 0.0f;
	view.raw[4] = right.y;
	view.raw[5] = up.y;
	view.raw[6] = -forward.y;
	view.raw[7] = 0.0f;
	view.raw[8] = right.z;
	view.raw[9] = up.z;
	view.raw[10] = -forward.z;
	view.raw[11] = 0.0f;
	view.raw[12] = -f32v3_dot(right, camera);
	view.raw[13] = -f32v3_dot(up, camera);
	view.raw[14] = f32v3_dot(forward, camera);
	view.raw[15] = 1.0f;
	return view;
}

static inline f32m4x4 m3dPerspective(f32 fovY, f32 aspect, f32 zNear, f32 zFar)
{
	f32 f = 1.0f / tanf(fovY * 0.5f);
	f32m4x4 mat;
	mat.raw[0] = f / aspect;
	mat.raw[1] = 0.0f;
	mat.raw[2] = 0.0f;
	mat.raw[3] = 0.0f;
	mat.raw[4] = 0.0f;
	mat.raw[5] = f;
	mat.raw[6] = 0.0f;
	mat.raw[7] = 0.0f;
	mat.raw[8] = 0.0f;
	mat.raw[9] = 0.0f;
	mat.raw[10] = (zFar + zNear) / (zNear - zFar);
	mat.raw[11] = -1.0f;
	mat.raw[12] = 0.0f;
	mat.raw[13] = 0.0f;
	mat.raw[14] = (2.0f * zFar * zNear) / (zNear - zFar);
	mat.raw[15] = 0.0f;
	return mat;
}

static inline f32v4 m3dMulVector4(const f32v4 v, const f32m4x4 m)
{
	f32v4 vOut;
	vOut.raw[0] = m.raw[0] * v.raw[0] + m.raw[4] * v.raw[1] + m.raw[8] * v.raw[2] + m.raw[12] * v.raw[3];
	vOut.raw[1] = m.raw[1] * v.raw[0] + m.raw[5] * v.raw[1] + m.raw[9] * v.raw[2] + m.raw[13] * v.raw[3];
	vOut.raw[2] = m.raw[2] * v.raw[0] + m.raw[6] * v.raw[1] + m.raw[10] * v.raw[2] + m.raw[14] * v.raw[3];
	vOut.raw[3] = m.raw[3] * v.raw[0] + m.raw[7] * v.raw[1] + m.raw[11] * v.raw[2] + m.raw[15] * v.raw[3];
	return vOut;
}

static inline bool m3dCloseEnough(f32 fCandidate, f32 fCompare, f32 fEpsilon)
{
	return (fabsf(fCandidate - fCompare) < fEpsilon);
}

static inline f32v2 m3dProjectXY(
	const f32m4x4 model_view,
	const f32m4x4 projection,
	const f32rect viewport,
	const f32v3 vPointIn)
{
	f32v4 back, forth;

	back.xyz = vPointIn;
	back.w = 1.f;

	forth = m3dMulVector4(back, model_view);
	back = m3dMulVector4(forth, projection);

	if (!m3dCloseEnough(back.w, 0.0f, 0.000001f)) {
		f32 div = 1.0f / back.w;
		back.x *= div;
		back.y *= div;
	}

	f32v2 out;
	out.x = back.x * 0.5f + 0.5f;
	out.y = back.y * 0.5f + 0.5f;
	out.x = (out.x * viewport.width) + viewport.x;
	out.y = (out.y * viewport.height) + viewport.y;
	return out;
}

#endif // M3D_H
