#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) { board.Initialize(width, height); }

  int GetScore() const { return score_; }
  bool HasLost() const { return game_over_; }

  void CreateOpponents();

  void OnMouseEvent(const graphics::MouseEvent &mouse_event) override;

  void Init() {
    player_.SetX(350);
    player_.SetY(280);
    board.AddMouseEventListener(*this);
    board.AddAnimationEventListener(*this);
  }

  void FilterIntersections() {
    for (int i = 0; i < opponent_.size(); i++) {
      if ((*opponent_[i]).GetIsActive() && player_.GetIsActive() &&
          player_.IntersectsWith(opponent_[i].get())) {
        (*opponent_[i]).SetIsActive(false);
        player_.SetIsActive(false);
        game_over_ = true;
      } else {
        for (int j = 0; j < friendlyprojectile_.size(); j++) {
          if ((*opponent_[i]).GetIsActive() &&
              (*friendlyprojectile_[j]).GetIsActive() &&
              (*friendlyprojectile_[j]).IntersectsWith(opponent_[i].get())) {
            (*opponent_[i]).SetIsActive(false);
            (*friendlyprojectile_[j]).SetIsActive(false);
            if (player_.GetIsActive()) {
              score_ += 1;
            }
          }
        }
      }
    }
    for (int i = 0; i < hostileprojectile_.size(); i++) {
      if ((*hostileprojectile_[i]).GetIsActive() && player_.GetIsActive() &&
          player_.IntersectsWith(hostileprojectile_[i].get())) {
        (*hostileprojectile_[i]).SetIsActive(false);
        player_.SetIsActive(false);
        game_over_ = true;
      }
    }
  }

  void MoveGameElements();

  void RemoveInactive();

  void LaunchProjectiles();

  void UpdateScreen();

  void Start();

  void OnAnimationStep() override;

  graphics::Image &GetGameScreen() { return board; }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return friendlyprojectile_;
  }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponent_; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return hostileprojectile_;
  }
  Player &GetPlayer() { return player_; }

 private:
  graphics::Image board;
  std::vector<std::unique_ptr<Opponent>> opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> hostileprojectile_;
  std::vector<std::unique_ptr<PlayerProjectile>> friendlyprojectile_;
  Player player_;
  bool game_over_ = false;
  int score_ = 0;
};
#endif
