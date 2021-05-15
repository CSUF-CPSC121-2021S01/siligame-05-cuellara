#include "game.h"
#include <string>

void Game::OnMouseEvent(const graphics::MouseEvent &mouse_event) {
  if (mouse_event.GetMouseAction() == graphics::MouseAction::kMoved ||
      mouse_event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int x_replaced = mouse_event.GetX() - player_.GetWidth() / 2;
    int y_replaced = mouse_event.GetY() - player_.GetHeight() / 2;
    int x_former = player_.GetX();
    int y_former = player_.GetY();

    player_.SetX(x_replaced);
    player_.SetY(y_replaced);

    if (player_.IsOutOfBounds(board)) {
      player_.SetX(x_former);
      player_.SetY(y_former);
    }
  }
  if (mouse_event.GetMouseAction() == graphics::MouseAction::kDragged ||
      mouse_event.GetMouseAction() == graphics::MouseAction::kPressed) {
    int x_replaced = mouse_event.GetX() - player_.GetWidth() / 2;
    int y_replaced = mouse_event.GetY() - player_.GetHeight() / 2;
    std::unique_ptr<PlayerProjectile> player_projectile =
        std::make_unique<PlayerProjectile>(x_replaced, y_replaced);
    friendlyprojectile_.push_back(std::move(player_projectile));
  }
}

void Game::OnAnimationStep() {
  if (opponent_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  board.Flush();
}

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opponent = std::make_unique<Opponent>();
  opponent_.push_back(std::move(opponent));
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_.size(); i++) {
    if ((*opponent_[i]).GetIsActive()) {
      (*opponent_[i]).Move(board);
    }
  }
  for (int i = 0; i < hostileprojectile_.size(); i++) {
    if ((*hostileprojectile_[i]).GetIsActive()) {
      (*hostileprojectile_[i]).Move(board);
    }
  }
  for (int i = 0; i < friendlyprojectile_.size(); i++) {
    if ((*friendlyprojectile_[i]).GetIsActive()) {
      (*friendlyprojectile_[i]).Move(board);
    }
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> opponent_projectile_ =
          std::make_unique<OpponentProjectile>(opponent_[i]->GetX(),
                                               opponent_[i]->GetY());
      hostileprojectile_.push_back(std::move(opponent_projectile_));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = opponent_.size() - 1; i >= 0; i--) {
    if (!(opponent_[i]->GetIsActive())) {
      opponent_.erase(opponent_.begin() + i);
    }
  }
  for (int i = hostileprojectile_.size() - 1; i >= 0; i--) {
    if (!(hostileprojectile_[i]->GetIsActive())) {
      hostileprojectile_.erase(hostileprojectile_.begin() + i);
    }
  }
  for (int i = friendlyprojectile_.size() - 1; i >= 0; i--) {
    if (!(friendlyprojectile_[i]->GetIsActive())) {
      friendlyprojectile_.erase(friendlyprojectile_.begin() + i);
    }
  }
}

void Game::UpdateScreen() {
  board.DrawRectangle(0, 0, board.GetWidth(), board.GetHeight(),
                      graphics::Color(255, 255, 255));
  std::string score_string_ = "Score " + std::to_string(score_);
  board.DrawText(10, 10, score_string_, 30, 0, 0, 0);
  if (game_over_ == true) {
    board.DrawText((board.GetWidth() * 0.5) - 200,
                   (board.GetHeight() * 0.5) - 200, "Game Over!", 80, 255, 20,
                   20);
  }
  if (player_.GetIsActive()) {
    player_.Draw(board);
  }
  for (int i = 0; i < opponent_.size(); i++) {
    if ((*opponent_[i]).GetIsActive()) {
      (*opponent_[i]).Draw(board);
    }
  }
  for (int i = 0; i < hostileprojectile_.size(); i++) {
    if ((*hostileprojectile_[i]).GetIsActive()) {
      (*hostileprojectile_[i]).Draw(board);
    }
  }
  for (int i = 0; i < friendlyprojectile_.size(); i++) {
    if ((*friendlyprojectile_[i]).GetIsActive()) {
      (*friendlyprojectile_[i]).Draw(board);
    }
  }
}

void Game::Start() { board.ShowUntilClosed(); }
