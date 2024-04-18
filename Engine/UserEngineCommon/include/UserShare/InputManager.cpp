#include "InputManager.h"

#include <memory>

namespace yougine
{
    InputManager::InputManager()
    {
        keycode_list =
        {
            { KeyBind::LeftClick, VK_LBUTTON },
            { KeyBind::RightClick, VK_RBUTTON },
        };

        key_info = new KeyInfo();
    }


    int InputManager::GetKeyCodeID(KeyBind code)
    {
        return keycode_list[code];
    }

    void InputManager::UpdateInput()
    {
        BYTE key_state[256];
        bool r = GetKeyboardState(key_state);

        int n_state = 0;

        // key_info->stateの内容をkey_info->state_oldにコピー
        memcpy(key_info->state_old, key_info->state, sizeof(key_info->state));

        // key_stateの内容をkey_info->stateにコピー
        memcpy(key_info->state, key_state, sizeof(key_state));
    }

    bool InputManager::IsPressKey(KeyBind bind)
    {
        auto keycode = GetKeyCodeID(bind);
        int keyinfo = key_info->state[keycode];
        bool isPress = keyinfo & 0x80;
        return isPress;
    }

    bool InputManager::IsPushKey(KeyBind bind)
    {
        auto keycode = GetKeyCodeID(bind);
        int keyinfo = key_info->state[keycode];
        int oldkeyinfo = key_info->state_old[keycode];
        bool isPress = keyinfo & 0x80;
        bool isoldPress = oldkeyinfo & 0x80;

        int state = isPress > isoldPress;
        return state;
    }

    bool InputManager::IsReleaseKey(KeyBind bind)
    {
        auto keycode = GetKeyCodeID(bind);
        int keyinfo = key_info->state[keycode];
        int oldkeyinfo = key_info->state_old[keycode];
        bool isPress = keyinfo & 0x80;
        bool isoldPress = oldkeyinfo & 0x80;

        int state = isPress < isoldPress;

        return state;
    }
}
