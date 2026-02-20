#pragma once
#include "Game/Public/Components/RenderComponent.h"

class LineRenderComponent : public RenderComponent
{
    friend class Actor;
public:
    LineRenderComponent() = delete;
    virtual void Render(exEngineInterface* EngineInterface) override;

    void SetStart(exVector2 Point1) { mPoint1 = Point1; }
    void SetEnd(exVector2 Point2) { mPoint2 = Point2; }

protected:
    LineRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, exVector2 Point1, exVector2 Point2, int Layer = 0);
private:
    exVector2 mPoint1;
    exVector2 mPoint2;
    int       mLayer;
};