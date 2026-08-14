#pragma once
#include <Level/Level.h>
#include <string>
#include <iostream>


// 메뉴 아이템 구조체.
struct TitleItem
{
	using OnSelected = void(*)();

	// 생성자.
	TitleItem(const std::string& text, OnSelected onSelected)
		: text(text), onSelected(onSelected)
	{}

	// 메뉴 텍스트.
	std::string text;

	// 메뉴를 선택했을 때 실행할 로직.
	OnSelected onSelected = nullptr;
};

class TitleLevel : public Craft::Level
{
public:
	TitleLevel();
protected:
	virtual void OnInitialized() override;
private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
private:
	// 현재 활성화된 메뉴 아이템 인덱스.
	int currentIndex = 0;

	// 선택된 메뉴 아이템의 색상.
	Craft::Color selectedColor = Craft::Color::Green;

	// 미선택된 메뉴 아이템의 색상.
	Craft::Color unselectedColor = Craft::Color::White;

	// 메뉴 아이템 배열.
	std::vector<std::unique_ptr<TitleItem>> itemList;
};
