#include "CPower_Line.h"

#include "CEffectParent.h"
#include "CEffect_Wind.h"
#include "CImageManager.h"

CPower_Line::CPower_Line(CVector position, CVector direction, double width,
                         double power, int duration)
    : CPower(position, power, duration), Direction(direction), Width(width) {
  Corner[0].x = position.x + cos(direction.x - Constant::PI / 2) * width / 2;
  Corner[0].y = position.y + sin(direction.x - Constant::PI / 2) * width / 2;
  Corner[1].x = position.x + cos(direction.x + Constant::PI / 2) * width / 2;
  Corner[1].y = position.y + sin(direction.x + Constant::PI / 2) * width / 2;
  Corner[2].x = position.x + cos(direction.x) * direction.y +
                cos(direction.x + Constant::PI / 2) * width / 2;
  Corner[2].y = position.y + sin(direction.x) * direction.y +
                sin(direction.x + Constant::PI / 2) * width / 2;
  Corner[3].x = position.x + cos(direction.x) * direction.y +
                cos(direction.x - Constant::PI / 2) * width / 2;
  Corner[3].y = position.y + sin(direction.x) * direction.y +
                sin(direction.x - Constant::PI / 2) * width / 2;

  ForceDirection.x = cos(direction.x);
  ForceDirection.y = sin(direction.x);
}

bool CPower_Line::isHit(CVector mPosition, double size) {
  //’¸“_‚Æ‚Ì“–‚½‚è”»’è
  for (int i = 0; i < 4; i++) {
    CVector dist(mPosition - Corner[i]);
    if (dist.getLength2() < size * size) return true;
  }

  //“à•”‚Ì“–‚½‚è”»’è
  {
    CVector A = Corner[1] - Corner[0];
    CVector B = mPosition - Corner[0];
    double th1 = atan2(A.cross(B), A.dot(B));
    A = Corner[3] - Corner[2];
    B = mPosition - Corner[2];
    double th2 = atan2(A.cross(B), A.dot(B));
    if (0.0 <= th1 && th1 <= Constant::PI / 2 && 0.0 <= th2 &&
        th2 <= Constant::PI / 2)
      return true;
  }

  //•Ó‚Æ‚Ì“–‚½‚è”»’è
  for (int i = 0; i < 4; i++) {
    CVector A = Corner[i] - mPosition;
    CVector D = Corner[(i + 1) % 4] - Corner[i];
    double t = -D.dot(A) / D.getLength2();
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    CVector T = Corner[i] + D * t;
    if ((mPosition - T).getLength() < size) return true;
  }

  return false;
}

void CPower_Line::ApplyForceToMover(CMover* m) {
  if (isHit(m->getPosition(), m->getSize()))
    m->ApplyAirForce(ForceDirection * Power /
                     ((m->getPosition() - Position).getLength() / Direction.y));
}

int CPower_Line::Update() {
  cnt++;
  if (cnt > duration) return 1;
  return 0;
}

void CPower_Line::Render() const {
  // CImageManager::getIns().find("effect_wind")->DrawModi(Corner[0].x,
  // Corner[0].y, Corner[1].x, Corner[1].y, 	Corner[2].x, Corner[2].y,
  //Corner[3].x, Corner[3].y, Constant::priority_effect, 0);
  for (int i = 0; i < 3; i++) {
    CEffectParent::RegisterEffect(std::make_shared<CEffect_Wind>(
        Position, Power, (float)Direction.x, Width, Direction.y));
  }
}
