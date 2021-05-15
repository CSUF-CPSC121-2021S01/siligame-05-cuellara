#include "player.h"
#include <iostream>
#include <string>
#include "cpputils/graphics/image.h"

void Player::Draw(graphics::Image &board) {
  board.DrawRectangle(21 + x_, 1 + y_, 9, 1, 41, 69, 30);
  board.DrawRectangle(20 + x_, 2 + y_, 11, 1, 41, 69, 30);
  board.DrawRectangle(19 + x_, 3 + y_, 13, 1, 41, 69, 30);
  board.DrawRectangle(18 + x_, 4 + y_, 15, 2, 36, 29, 96);
  board.DrawRectangle(24 + x_, 6 + y_, 3, 31, 36, 29, 96);
  board.DrawRectangle(18 + x_, 6 + y_, 6, 31, 41, 69, 30);
  board.DrawRectangle(27 + x_, 6 + y_, 6, 31, 41, 69, 30);
  board.DrawRectangle(14 + x_, 19 + y_, 4, 19, 36, 29, 96);
  board.DrawRectangle(33 + x_, 19 + y_, 4, 19, 36, 29, 96);
  board.DrawRectangle(10 + x_, 21 + y_, 4, 19, 0, 0, 0);
  board.DrawRectangle(37 + x_, 21 + y_, 4, 19, 0, 0, 0);
}

void PlayerProjectile::Draw(graphics::Image &board) {
  board.DrawRectangle(1 + x_, 0 + y_, 3, 5, 36, 29, 96);
}

void Player::Move(const graphics::Image &board) {}

void PlayerProjectile::Move(const graphics::Image &board) {
  if (IsOutOfBounds(board)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ - 3);
  }
}
