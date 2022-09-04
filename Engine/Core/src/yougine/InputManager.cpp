#include "InputManager.h"

namespace yougine
{
    InputManager::InputManager()
    {
        keycode_list =
        {
            { KeyBind::RightClick, 0x02 },
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

        for (int i = 0; i < (int)KeyBind::BindMax; i++)
        {
            if (key_state[GetKeyCodeID((KeyBind)i)] & 0x80)
            {
                n_state |= (1 << i);
            }
        }

        key_info->state_old = key_info->state;
        key_info->state = n_state;
    }

    bool InputManager::IsPressKey(KeyBind bind)
    {
        int bit = (1 << (int)bind);
        return key_info->state & bit;
    }

    bool InputManager::IsPushKey(KeyBind bind)
    {
        int bit = (1 << (int)bind);
        int state = key_info->state & ~(key_info->state_old);
        return state & bit;
    }

    bool InputManager::IsReleaseKey(KeyBind bind)
    {
        int bit = (1 << (int)bind);
        int state = key_info->state_old & ~(key_info->state);
        return state & bit;
    }
}