#pragma once
class Position {
public:
    Position(int ligne, int colonne) : x_(ligne), y_(colonne) {}

    int x() const { return x_; }
    int y() const { return y_; }

private:
    int x_;
    int y_;
};