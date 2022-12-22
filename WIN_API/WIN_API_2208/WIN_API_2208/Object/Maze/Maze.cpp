#include "framework.h"
#include "Maze.h"

Maze::Maze()
{
	Vector2 offset = { 400, 150 };

	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			shared_ptr<Block> block = make_shared<Block>();
			block->SetType(Block::Type::DISABLE);
			Vector2 distance = { 17.0f * x, 17.0f * y };
			block->SetPosition(offset + distance);

			_blocks.push_back(block);
			_blockMatrix[y][x] = block;
		}
	}
	CreateMaze();
}

Maze::~Maze()
{
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			_blockMatrix[y][x] = nullptr;
		}
	}
}

void Maze::Update()
{
	for (auto block : _blocks)
		block->Update();
}

void Maze::Render(HDC hdc)
{
	for (auto block : _blocks)
		block->Render(hdc);

	wstring maze = L"Maze!!";
	TextOut(hdc, CENTER_X - 30, 100, maze.c_str(), maze.size());
}

void Maze::CreateMaze()
{
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blockMatrix[y][x]->SetType(Block::Type::DISABLE);
			}
			else
				_blockMatrix[y][x]->SetType(Block::Type::ABLE);
		}
	}

	//랜덤으로 우측 혹은 아래로 길을 뚫는 작업
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			// 시작점
			if (x == 1 && y == 1)
			{
				_blockMatrix[y][x]->SetType(Block::Type::START);
			}

			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 미로가 끝나는 지점이면 길 뚫기 중지
			if (x == _poolCountX - 2 && y == _poolCountY - 2) // 23,23이 끝 점이기 때문에...
			{
				// 끝나는 지점임을 표시
				_blockMatrix[y][x]->SetType(Block::Type::END);
				continue;
			}

			// 랜덤으로 우측 혹은 아래로만 뚫었을 때 길이 안생기는 것 예외처리
			if (y == _poolCountY - 2)
			{
				_blockMatrix[y][x + 1]->SetType(Block::Type::ABLE); // 전부 아래쪽으로만 간 경우
				continue;
			}

			if (x == _poolCountX - 2)
			{
				_blockMatrix[y + 1][x]->SetType(Block::Type::ABLE); // 전부 오른쪽으로만 간 경우
				continue;
			}

			const int randValue = rand() % 2;
			if (randValue == 0)
				_blockMatrix[y][x + 1]->SetType(Block::Type::ABLE);
			else
				_blockMatrix[y + 1][x]->SetType(Block::Type::ABLE);
		}
	}
}

