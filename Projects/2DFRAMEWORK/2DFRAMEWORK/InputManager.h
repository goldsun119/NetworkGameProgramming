#pragma once
class InputManager :public CSingleTonBase<InputManager> //: public FrameWork
{
public:
	InputManager();
	~InputManager();

public:
	void SetKeyState();
};

#pragma once
