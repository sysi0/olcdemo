#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class gra : public olc::PixelGameEngine
{
public:
	gra()
	{
		sAppName = "gra";
	}

private:
	int level = 0;

	float posX = 0.0f;
	float posY = 0.0f;
	float speed = 0.1f / 40.0f;
	int dir = 1;

	int map[16][16];

	float fTargetFrameTime = 1.0f / 100.0f; // Virtual FPS of 100fps
	float fAccumulatedTime = 0.0f;


public:

	void loadLevel() {

		std::ifstream file{ "levels/map" + std::to_string(level) + ".txt" };
		if (!file.is_open()) return;
		char ch;
		for (int i{}; i != 16; ++i) {
			for (int j{}; j != 16; ++j) {
				file >> ch;
				map[i][j] = (int)ch - 48;
			}
		}

	}

	void move() {
		bool ag = 1;
		switch (dir) {
			
			case 1: // Right
				if (posX < 15) {

					if (map[(int)posY][(int)posX + 1] != 1){

						if ((map[(int)posY][(int)posX + 2] == 1) && map[(int)posY][(int)posX + 1] == 3) {
							break;
						}
						else if (map[(int)posY][(int)posX + 1] == 3 && (int)posX + 1 == 15) {
							break;
						}
						else
						{
							posX += speed;
						}

					}

				}

				break;

			case 2: // Down
				if (posY < 15) {

					if (map[(int)posY + 1][(int)posX] != 1) {

						if ((map[(int)posY + 2][(int)posX] == 1) && map[(int)posY + 1][(int)posX] == 3) {
							break;
						}
						else if (map[(int)posY + 1][(int)posX] == 3 && (int)posY + 1 == 15) {
							break;
						}
						else {
							posY += speed;
						}

					}

				}
				break;

			case 3: // Left

				if (posX > 0) {

					if (map[(int)posY][(int)posX - 1] != 1) {

						if ((map[(int)posY][(int)posX - 2] == 1) && map[(int)posY][(int)posX - 1] == 3) {
							break;
						}
						else if (map[(int)posY][(int)posX - 1] == 3 && (int)posX - 1 == 0) {
							break;
						}
						else {
							posX -= speed;
						}

					}

				}

				break;

			case 4: // Up
				if (posY > 0) {

					if (map[(int)posY - 1][(int)posX] != 1) {

						if ((map[(int)posY - 2][(int)posX] == 1) && map[(int)posY - 1][(int)posX] == 3) {
							break;
						}
						else if (map[(int)posY - 1][(int)posX] == 3 && (int)posY - 1 == 0) {
							break;
						}
						else {
							posY -= speed;
						}

					}

				}
				break;
		}
		//std::cout << std::to_string(posX) + " " + std::to_string(posY) << std::endl;
	}

	bool OnUserCreate() override
	{
		loadLevel();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime)
		{
			fAccumulatedTime -= fTargetFrameTime;
			fElapsedTime = fTargetFrameTime;
		}
		else

		Clear(olc::BLACK);

		//if ((GetKey(olc::Key::W).bHeld) && (posY > 0) && (map[(int)posY - 1][(int)posX] != 1)) {
		//	posY -= speed;
		//	dir = 4;
		//}
		//if ((GetKey(olc::Key::S).bHeld) && (posY < 15) && (map[(int)posY + 1][(int)posX] != 1)) {
		//	posY += speed;
		//	dir = 2;
		//}
		//if ((GetKey(olc::Key::A).bHeld) && (posX > 0) && (map[(int)posY][(int)posX - 1] != 1)) {
		//	posX -= speed;
		//	dir = 3;
		//}
		//if ((GetKey(olc::Key::D).bHeld) && (posX < 15) && (map[(int)posY][(int)posX + 1] != 1)) {
		//	posX += speed;
		//	dir = 1;
		//}

		if (GetKey(olc::Key::D).bHeld) {
			dir = 1;
			move();
		}
		else if (GetKey(olc::Key::A).bHeld) {
			dir = 3;
			move();
		}
		else if (GetKey(olc::Key::W).bHeld) {
			dir = 4;
			move();
		}
		else if (GetKey(olc::Key::S).bHeld) {
			dir = 2;
			move();
		}

		if (GetKey(olc::Key::R).bPressed) {
			posX = 0.0f;
			posY = 0.0f;
			loadLevel();
		}


		

		if (map[(int)posY][(int)posX] == 3) {
			map[(int)posY][(int)posX] = 0;
			switch (dir) {
			case 1:
				if (map[(int)posY][(int)posX + 1] == 0) {
					map[(int)posY][(int)posX + 1] = 3;
				}
				break;
			case 2:
				if (map[(int)posY + 1][(int)posX] == 0) {
					map[(int)posY + 1][(int)posX] = 3;
				}
				break;
			case 3:
				if (map[(int)posY][(int)posX - 1] == 0) {
					map[(int)posY][(int)posX - 1] = 3;
				}
				break;
			case 4:
				if (map[(int)posY - 1][(int)posX] == 0) {
					map[(int)posY - 1][(int)posX] = 3;
				}
				break;
			}
		}


		for (int i = 0; i < 16; i++){
			for (int j = 0; j < 16; j++) {
				if (map[i][j] == 1) {
					Draw(j, i, olc::Pixel(olc::WHITE));
				}
				if (map[i][j] == 2) {
					Draw(j, i, olc::Pixel(olc::BLUE));
				}
				if (map[i][j] == 3) {
					Draw(j, i, olc::Pixel(olc::RED));
				}
				if (map[i][j] == 4) {
					Draw(j, i, olc::Pixel(olc::DARK_RED));
				}
			}
		}
		


		Draw(posX, posY, olc::Pixel(olc::GREEN));

		if (map[(int)posY][(int)posX] == 2) {
			int apprc = 0;
			for (int i{}; i != 16; ++i) {
				for (int j{}; j != 16; ++j) {
					if (map[i][j] == 3) {
						apprc++;
					}
				}
			}

			if (apprc == 0) {
				posX = 0.0f;
				posY = 0.0f;
				level++;
				loadLevel();
			}
		}

		return true;
	}
};

int main()
{
	gra demo;
	if (demo.Construct(16, 16, 32, 32))
		demo.Start();
	return 0;
}