//	b2d.h
//	created by Wayne.

#pragma once

#ifdef B2D_EXPORTS
#	define _bs_api __declspec( dllexport )
#else
#	define _bs_api __declspec( dllimport )
#endif

#define _bs_begin	namespace bosi {
#define _bs_end		}
#define _bs_ns		::bosi



_bs_begin

struct Vertex {
	float x, y;
	unsigned int color;
	float u, v;
};

enum PrimitiveType {
	kLines = 1,
	kTriangles = 2,
};

enum AlphaMode {
	kAlpha_None = 0,
	kAlpha_Blend,
	kAlpha_Additive
};

struct MouseEvent {
	bool pressed;
	unsigned int button;
	int x, y;
};

struct KeyEvent {
	bool pressed;
	unsigned int code;
};

struct PointI {
	int x;
	int y;
};

struct SizeI {
	int width;
	int height;
};

typedef long Texture;
typedef long Font;

bool _bs_api startup(unsigned int width, unsigned int height, const wchar_t *caption);
void _bs_api cleanup();

void _bs_api setMouseEventRoutine(void (*routine)(const MouseEvent *));
void _bs_api setKeyEventRoutine(void (*routine)(const KeyEvent *));
PointI _bs_api getMousePosition();

bool _bs_api run();
void _bs_api quit();

unsigned int _bs_api time();

bool _bs_api begin();
void _bs_api end();

void _bs_api clear(unsigned int color);
void _bs_api draw(PrimitiveType type, unsigned int count, const Vertex *vertices);
void _bs_api draw(PrimitiveType type, unsigned int count, const Vertex *vertices, unsigned int numVertices, const unsigned short *indices);

Texture _bs_api loadTextureFromPNG(const wchar_t *fileName);
void _bs_api freeTexture(Texture texture);

SizeI _bs_api getTextureSize(Texture texture);
SizeI _bs_api getTextureContentSize(Texture texture);

void _bs_api setTexture(Texture texture);
Texture _bs_api getTexture();

void _bs_api setAlphaMode(AlphaMode mode);
AlphaMode _bs_api getAlphaMode();

void _bs_api setViewMatrix(float mat[9]);

Font _bs_api createFont(const wchar_t *fontFileName, unsigned int fontHeight);
void _bs_api freeFont(Font font);

void _bs_api drawText(Font font, float x, float y, unsigned int color, const wchar_t *text, unsigned int length = -1);

_bs_end