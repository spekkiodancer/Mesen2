#pragma once
#include "pch.h"
#include <deque>
#include "BaseControlDevice.h"

class Emulator;

class RewindData
{
private:
	vector<uint8_t> SaveStateData;

public:
	std::deque<ControlDeviceState> InputLogs[BaseControlDevice::PortCount];
	int32_t FrameCount = 0;
	bool EndOfSegment = false;

	void GetStateData(stringstream &stateData);

	void LoadState(Emulator* emu);
	void SaveState(Emulator* emu);
};
