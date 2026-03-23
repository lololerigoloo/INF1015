#pragma once
#include "Noeud.hpp"
#include "gsl/gsl_assert"

template <typename T> class ListeLiee;

template <typename T>
class Iterateur
{
	friend class ListeLiee<T>;

public:
	Iterateur(Noeud<T> *position) : position_(position) {}

	void avancer()
	{
		Expects(position_ != nullptr);
		position_ = position_->suivant_;
	}

	void reculer()
	{
		Expects(position_ != nullptr);
		position_ = position_->precedent_;
	}

	T &operator*() { return position_->donnee_; }
	T &operator*() const { return position_->donnee_; }
	T *operator->() const { return &(position_->donnee_); }

	bool operator==(const Iterateur<T> &it) const = default;
	bool operator!=(const Iterateur<T> &it) const { return !(*this == it); }

	Iterateur<T> &operator++()
	{
		avancer();
		return *this;
	}
	Iterateur<T> &operator--()
	{
		reculer();
		return *this;
	}
	Iterateur<T> operator++(int)
	{
		Iterateur<T> temp = *this;
		avancer();
		return temp;
	}
	Iterateur<T> operator--(int)
	{
		Iterateur<T> temp = *this;
		reculer();
		return temp;
	}

private:
	Noeud<T> *position_;
};