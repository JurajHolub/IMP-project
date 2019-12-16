#include "display.h"

const unsigned MAP[] = {
	PANEL_1, //Panel
	PANEL_2, //Panel
	PANEL_3, //Panel
	SEG_C, //Panel
	SEG_E,
	SEG_B,
	SEG_G,
	PANEL_4,
	SEG_A,
	SEG_D,
	SEG_F,
};

PanelSegment actualizePanelSegment()
{
	static PanelSegment segment = Segment1;
	segment = (segment + 1) % 4;
	return segment;
}

segment_t actualizeLedSegment()
{
	segment_t result;
	static LedSegment segment = SegmentA;
	if (segment == 0) result.panel = actualizePanelSegment();
	segment = (segment + 1) % 8;
	result.led = 4 + segment;
	return result;
}

unsigned mapPort(unsigned port)
{
	return MAP[port];
}
