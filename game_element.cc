#include "game_element.h"

bool GameElement::IntersectsWith(GameElement *intersectelement) {
  if (GetX() < intersectelement->GetX() + intersectelement->GetWidth()) {
    if (intersectelement->GetX() < GetX() + GetWidth()) {
      if (GetY() < intersectelement->GetY() + intersectelement->GetWidth()) {
        if (intersectelement->GetY() < GetY() + GetHeight()) {
          return true;
        }
      }
    }
  }
  return false;
}
bool GameElement::IsOutOfBounds(const graphics::Image &board) {
  if (x_ < 0) {
    return true;
  }
  if ((x_ + kWidth_) > board.GetWidth()) {
    return true;
  }
  if (y_ < 0) {
    return true;
  }
  if ((y_ + kHeight_) > board.GetHeight()) {
    return true;
  }
  return false;
}
