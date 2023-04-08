#include "Color.h"

// rand include
#include <stdlib.h>


SDL_Color Color::GetColor(ColorType colorType)
{	
	switch (colorType)
	{
		case ColorType::White:	return { 255, 255, 255, 255 };
		case ColorType::Red:    return { 255, 0, 0, 255 };
		case ColorType::Green:  return { 0, 255, 0, 255 };
		case ColorType::Blue:   return { 0, 0, 255, 255 };
		case ColorType::Yellow: return { 255, 255, 0, 255 };
		case ColorType::Orange: return { 255, 165, 0, 255 };
		case ColorType::Purple: return { 128, 0, 128, 255 };
		case ColorType::Pink:   return { 255, 192, 203, 255 };
		case ColorType::Gray:   return { 128, 128, 128, 255 };
		case ColorType::LightGray:   return { 211, 211, 211, 255 };
		case ColorType::DarkGray:    return { 169, 169, 169, 255 };
		case ColorType::LightBlue:   return { 173, 216, 230, 255 };
		case ColorType::LightGreen:  return { 144, 238, 144, 255 };
		case ColorType::LightRed:    return { 255, 182, 193, 255 };
		case ColorType::LightYellow: return { 255, 255, 224, 255 };
		case ColorType::LightOrange: return { 255, 228, 181, 255 };
		case ColorType::LightPurple: return { 221, 160, 221, 255 };
		case ColorType::LightPink:   return { 255, 182, 193, 255 };
		case ColorType::LightBrown:  return { 210, 180, 140, 255 };
		case ColorType::DarkBlue:    return { 0, 0, 139, 255 };
		case ColorType::DarkGreen:   return { 0, 100, 0, 255 };
		case ColorType::DarkRed:     return { 139, 0, 0, 255 };
		case ColorType::DarkYellow:  return { 128, 128, 0, 255 };
		case ColorType::DarkOrange:  return { 255, 140, 0, 255 };
		case ColorType::DarkPurple:  return { 128, 0, 128, 255 };
		case ColorType::DarkPink:    return { 255, 20, 147, 255 };
		case ColorType::DarkBrown:   return { 139, 69, 19, 255 };
		case ColorType::Black:  return { 0, 0, 0, 255 };
		case ColorType::Transparent: return { 0, 0, 0, 0 };
		default: return { 255, 255, 255, 255 };
	}
}

SDL_Color Color::GetRandomColor()
{
	return GetColor (static_cast<ColorType>(rand() % 26));
}