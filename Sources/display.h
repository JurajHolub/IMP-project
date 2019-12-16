/**
 * @author Juraj Holub <xholub40>
 * @brief Mapping of Led displey pins to MCU pins.
 * @date December 2019
 * @project VUT FIT - IMP
 */

#ifndef SOURCES_DISPLAY_H_
#define SOURCES_DISPLAY_H_

#define SEG_D 0x20000000
#define SEG_C 0x10000000
#define SEG_E 0x8000000
#define SEG_F 0x4000000
#define SEG_A 0x2000000
#define SEG_H 0x1000000
#define SEG_G 0x800
#define SEG_B 0x400
#define PANEL_4  0x200
#define PANEL_1  0x100
#define PANEL_3  0x80
#define PANEL_2  0x40

typedef enum PanelSegment_e {
	Segment0=0, Segment1, Segment2, Segment3
} PanelSegment;

typedef enum LedSegment_e {
	SegmentA=0, SegmentB, SegmentC, SegmentD, SegmentE, SegmentF, SegmentG, SegmentH
} LedSegment;

typedef enum Map_e {
	Port0=0, Port1, Port2, Port3, Port4, Port5, Port6, Port7, Port8, Port9, Port10, Port11
} Map;

typedef struct segment_s {
	PanelSegment panel;
	LedSegment led;
} segment_t;

PanelSegment actualizePanelSegment();
segment_t actualizeLedSegment();
unsigned mapPort(unsigned port);
void turnZero();
void turnOne();

#endif /* SOURCES_DISPLAY_H_ */
