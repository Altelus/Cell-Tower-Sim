#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include <string>

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#define M_PIX 3.14159265358979323846

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

void setLineWidth(float width);
void setColor(float red, float green, float blue);
void drawLine(float startX,float startY, float endX, float endY);
void drawRectangle(bool filled, float cornerX, float cornerY, int width, int height, float theta);
void drawCircle(int subdivisions, float radius, float centerX, float centerY, float lineWidth);
void drawFilledCircle(int subdivisions, float radius, float centerX, float centerY);
void drawTriangle(bool filled, float p0x, float p0y, float p1x, float p1y, float p2x, float p2y);
void drawText(std::string s, float posX, float posY);
void drawTextLarge(std::string s, float posX, float posY);

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#endif