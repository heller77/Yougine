#pragma once
#include <Windows.h>
#include <map>
#include <iostream>

namespace yougine
{
    enum class KeyBind
    {
        LeftClick,
        RightClick,
        BindMax,
    };

    class KeyInfo
    {
    public:
        int state;
        int state_old;
    };

    class InputManager
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