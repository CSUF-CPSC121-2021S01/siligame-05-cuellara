#include "opponent.h"
#include <iostream>
#include "cpputils/graphics/image.h"

void OpponentProjectile::Draw(graphics::Image &board) {
  graphics::Color red(171, 16, 16);
  board.DrawRectangle(1 + x_, 0 + y_, 3, 5, red);
}
void Opponent::Draw(graphics::Image &board) {
  graphics::Color black(0, 0, 0);
  graphics::Color red(171, 16, 16);
  board.DrawRectangle(21 + x_, 1 + y_, 9, 1, black);
  board.DrawRectangle(20 + x_, 2 + y_, 11, 1, black);
  board.DrawRectangle(19 + x_, 3 + y_, 13, 1, black);
  board.DrawRectangle(18 + x_, 4 + y_, 15, 2, red);
  board.DrawRectangle(24 + x_, 6 + y_, 3, 31, red);
  board.DrawRectangle(18 + x_, 6 + y_, 6, 31, black);
  board.DrawRectangle(27 + x_, 6 + y_, 6, 31, black);
  board.DrawRectangle(14 + x_, 19 + y_, 4, 19, red);
  board.DrawRectangle(33 + x_, 19 + y_, 4, 19, red);
  board.DrawRectangle(10 + x_, 21 + y_, 4, 19, black);
  board.DrawRectangle(37 + x_, 21 + y_, 4, 19, black);
}

void Opponent::Move(const graphics::Image &board) {
  if (IsOutOfBounds(board)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ + 1);
  }
}

void OpponentProjectile::Move(const graphics::Image &board) {
  if (IsOutOfBounds(board)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ + 3);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  projectile_count_ += 1;
  if (projectile_count_ % 20 == 0) {
    std::unique_ptr<OpponentProjectile> new_launch =
        std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(new_launch);
  } else {
    return nullptr;
  }
}
