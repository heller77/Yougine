#pragma once
#include <map>
#include <string>

#include "UserShare/MacroDifHeader.h"
#include <Windows.h>
namespace yougine
{
    /**
     * \brief キーの種類（ここにあるもののみ対応）
     */
    enum class EXPORT VirtualKey
    {
        MouseLeftClick,
        MouseRightClick,
        MouseMiddleClick,
        Tab,
        Space,
        LeftCtrl,
        RightCtrl,
        Shift,
        LeftAlt,
        RightAlt,
        Enter,
        Esc,
        At,
        LeftArrow,
        RightArrow,
        UpperArrow,
        DownArrow,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        zero, one, two, three, four, five, six, seven, eight, nine,
    };
    std::map<VirtualKey, int> GenerateKeyBind();
    std::string GetKeyName(VirtualKey key);
}
