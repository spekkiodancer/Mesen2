#pragma once
#include "stdafx.h"
#include "GbTypes.h"
#include "../Utilities/ISerializable.h"

class Console;
class Gameboy;
class GbMemoryManager;
class GbDmaController;

class GbPpu : public ISerializable
{
private:
	Console* _console = nullptr;
	Gameboy* _gameboy = nullptr;
	GbPpuState _state = {};
	GbMemoryManager* _memoryManager = nullptr;
	GbDmaController* _dmaController = nullptr;
	uint16_t* _outputBuffers[2] = {};
	uint16_t* _currentBuffer = nullptr;

	uint16_t* _eventViewerBuffers[2] = {};
	uint16_t* _currentEventViewerBuffer = nullptr;
	EvtColor _evtColor = EvtColor::HBlank;
	int16_t _prevDrawnPixels = 0;

	uint8_t* _vram = nullptr;
	uint8_t* _oam = nullptr;

	uint64_t _lastFrameTime = 0;

	GbPpuFifo _bgFifo;
	GbPpuFetcher _bgFetcher;

	GbPpuFifo _oamFifo;
	GbPpuFetcher _oamFetcher;

	int16_t _drawnPixels = 0;
	uint8_t _fetchColumn = 0;
	bool _fetchWindow = false;

	int16_t _fetchSprite = -1;
	uint8_t _spriteCount = 0;
	uint8_t _spriteX[10] = {};
	uint8_t _spriteIndexes[10] = {};

	__forceinline void ProcessPpuCycle();

	__forceinline void ExecCycle();
	__forceinline void RunDrawCycle();
	__forceinline void RunSpriteEvaluation();
	void ResetRenderer();
	void ClockSpriteFetcher();
	void FindNextSprite();
	__forceinline void ClockTileFetcher();
	__forceinline void PushSpriteToPixelFifo();
	__forceinline void PushTileToPixelFifo();

	__forceinline void ChangeMode(PpuMode mode);
	__forceinline void UpdateLyCoincidenceFlag();
	__forceinline void UpdateStatIrq();

	void WriteCgbPalette(uint8_t& pos, uint16_t* pal, bool autoInc, uint8_t value);

public:
	virtual ~GbPpu();

	void Init(Console* console, Gameboy* gameboy, GbMemoryManager* memoryManager, GbDmaController* dmaController, uint8_t* vram, uint8_t* oam);

	GbPpuState GetState();
	uint16_t* GetEventViewerBuffer();
	uint16_t* GetPreviousEventViewerBuffer();
	void GetPalette(uint16_t out[4], uint8_t palCfg);
	
	uint32_t GetFrameCount();
	bool IsLcdEnabled();
	PpuMode GetMode();

	void Exec();

	void SendFrame();

	uint8_t Read(uint16_t addr);
	void Write(uint16_t addr, uint8_t value);

	uint8_t ReadVram(uint16_t addr);
	void WriteVram(uint16_t addr, uint8_t value);

	uint8_t ReadOam(uint8_t addr);
	void WriteOam(uint8_t addr, uint8_t value, bool forDma);

	uint8_t ReadCgbRegister(uint16_t addr);
	void WriteCgbRegister(uint16_t addr, uint8_t value);
	
	void Serialize(Serializer& s) override;
};
