#pragma once
#include <Windows.h>
#include <map>
#include <iostream>

#include "UserShare/MacroDifHeader.h"


namespace yougine
{
    enum class EXPORT KeyBind
    {
        LeftClick,
        RightClick,

    };

    class EXPORT KeyInfo
    {
    public:
        BYTE state[256];
        BYTE state_old[256];
    };

    class EXPORT InputManager
    {
    private:
        KeyInfo* key_info;
        std::map<KeyBind, int> keycode_list;

    public:
        InputManager();
        int GetKeyCodeID(KeyBind code);
        void UpdateInput();
        bool IsPressKey(KeyBind);
        bool IsPushKey(KeyBind);
        bool IsReleaseKey(KeyBind);
    };
}