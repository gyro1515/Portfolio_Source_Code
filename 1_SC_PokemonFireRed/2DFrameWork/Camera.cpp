#include "framework.h"

Camera::Camera()
{
    //첫 카메라 위치
    position.x = 0.0f;
    position.y = 0.0f;

    //뷰포트
    viewport.x = 0.0f;
    viewport.y = 0.0f;

    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}

void Camera::Set()
{
    //역이동 행렬
    V = Matrix::CreateTranslation(-position.x, -position.y, 0.0f);
    //프로젝션 -> 투영 행렬
    P = Matrix::CreateOrthographic(app.GetWidth(), app.GetHeight(), 0.0f, 10.0f); // 원본
    //P = Matrix::CreateOrthographic(app.GetWidth() * 4.6f, app.GetHeight() * 4.6f, 0.0f, 10.0f); // 동굴 테스트용

    VP = V * P;
}

void Camera::ResizeScreen()
{
    /*viewport.x = 100.0f;
    viewport.y = 100.0f;*/

    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}
