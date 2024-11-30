#include "Light.h"

void Light::draw() const {
    BeginBlendMode(BLEND_ADDITIVE);
    DrawCircleGradient(
        position.x,
        position.y,
        radius,
        ColorAlpha(
            ColorFromHSV(
                51,
                66,
                89
            ),
            0.4f
        ),
        ColorAlpha(
            WHITE,
            0
        )
    );
    EndBlendMode();
}
