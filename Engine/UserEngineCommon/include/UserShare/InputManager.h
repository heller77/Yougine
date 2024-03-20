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
        BindMax,
    };

    class EXPORT KeyInfo
    {
    public:
        int state;
        int state_old;
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