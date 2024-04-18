#pragma once
#include <Windows.h>
#include <map>
#include <iostream>
#include <vector>

#include "UserShare/MacroDifHeader.h"
#include "utilitys/VirtualKey.h"

namespace yougine
{

    class EXPORT KeyInfo
    {
    public:
        /**
         * \brief 現在のフレームでのキー入力の情報
         */
        BYTE state[256];

        /**
         * \brief 1フレーム前のキー入力の情報
         */
        BYTE state_old[256];
    };

    class EXPORT InputManager
    {
    private:
        KeyInfo* key_info;
        std::map<VirtualKey, int> keycode_list;

    public:
        InputManager();
        int GetKeyCodeID(VirtualKey code);
        void UpdateInput();

        /**
         * \brief 今押されてるかどうか
         * \return 今押されてるかどうか
         */
        bool IsPressKey(VirtualKey);

        /**
         * \brief 押され始めたかどうか
         * \return 押され始めたかどうか
         */
        bool IsPushKey(VirtualKey);

        /**
         * \brief キーが離されたかどうか
         * \return キーが離されたかどうか
         */
        bool IsReleaseKey(VirtualKey);

        /**
         * \brief 今入力されているキーを出力
         */
        void PrintNowPressKey();
    };
}