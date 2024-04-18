#include "InputManager.h"

#include <memory>

namespace yougine
{
    InputManager::InputManager()
    {
        keycode_list = GenerateKeyBind();

        key_info = new KeyInfo();
    }


    int InputManager::GetKeyCodeID(VirtualKey code)
    {
        auto iterator = keycode_list.find(code);

        if (iterator != keycode_list.end()) {
            return keycode_list[code];
        }
        else
        {
            return -1;
        }
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

    bool InputManager::IsPressKey(VirtualKey bind)
    {
        auto keycode = GetKeyCodeID(bind);
        if (keycode == -1)
        {
            return false;
        }
        int keyinfo = key_info->state[keycode];
        bool isPress = keyinfo & 0x80;
        return isPress;
    }

    bool InputManager::IsPushKey(VirtualKey bind)
    {
        auto keycode = GetKeyCodeID(bind);
        //登録されたキーコードでなければ
        if (keycode == -1)
        {
            return false;
        }
        int keyinfo = key_info->state[keycode];
        int oldkeyinfo = key_info->state_old[keycode];
        bool isPress = keyinfo & 0x80;
        bool isoldPress = oldkeyinfo & 0x80;

        int state = isPress > isoldPress;
        return state;
    }

    bool InputManager::IsReleaseKey(VirtualKey bind)
    {
        auto keycode = GetKeyCodeID(bind);
        //登録されたキーコードでなければ
        if (keycode == -1)
        {
            return false;
        }

        int keyinfo = key_info->state[keycode];
        int oldkeyinfo = key_info->state_old[keycode];
        bool isPress = keyinfo & 0x80;
        bool isoldPress = oldkeyinfo & 0x80;

        int state = isPress < isoldPress;

        return state;
    }

    void InputManager::PrintNowPressKey()
    {
        bool is_press_anykey = false;
        // 全キーバインドをチェックするループ
        for (int key = static_cast<int>(VirtualKey::MouseLeftClick); key <= static_cast<int>(VirtualKey::nine); ++key) {
            if (this->IsPressKey(static_cast<VirtualKey>(key))) {
                if (!is_press_anykey)
                {
                    std::cout << "[input] : ";
                }
                std::cout << GetKeyName(static_cast<VirtualKey>(key)) << " ";
                is_press_anykey = true;
            }
        }
        if (is_press_anykey) {
            std::cout << std::endl;
        }
    }
}
