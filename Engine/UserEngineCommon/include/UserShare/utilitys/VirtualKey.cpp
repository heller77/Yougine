#include "VirtualKey.h"

std::map<yougine::VirtualKey, int> yougine::GenerateKeyBind()
{
    std::map<yougine::VirtualKey, int> keycode_list =
    {
        {VirtualKey::MouseLeftClick, VK_LBUTTON},
        {VirtualKey::MouseRightClick, VK_RBUTTON},
        {VirtualKey::MouseMiddleClick, VK_MBUTTON},
        {VirtualKey::Tab, VK_TAB},
        {VirtualKey::Space, VK_SPACE},
        {VirtualKey::LeftCtrl, VK_LCONTROL},
        {VirtualKey::RightCtrl, VK_RCONTROL},
        {VirtualKey::Shift, VK_SHIFT},
        {VirtualKey::LeftAlt, VK_LMENU},
        {VirtualKey::RightAlt, VK_RMENU},
        {VirtualKey::Enter, VK_RETURN},
        {VirtualKey::Esc, VK_ESCAPE},
        {VirtualKey::At,VK_OEM_3},
        {VirtualKey::LeftArrow,VK_LEFT},
        {VirtualKey::RightArrow,VK_RIGHT},
        {VirtualKey::UpperArrow,VK_UP},
        {VirtualKey::DownArrow,VK_DOWN},
        {VirtualKey::A, int('A')},
        {VirtualKey::B, int('B')},
        {VirtualKey::C, int('C')},
        {VirtualKey::D, int('D')},
        {VirtualKey::E, int('E')},
        {VirtualKey::F, int('F')},
        {VirtualKey::G, int('G')},
        {VirtualKey::H, int('H')},
        {VirtualKey::I, int('I')},
        {VirtualKey::J, int('J')},
        {VirtualKey::K, int('K')},
        {VirtualKey::L, int('L')},
        {VirtualKey::M, int('M')},
        {VirtualKey::N, int('N')},
        {VirtualKey::O, int('O')},
        {VirtualKey::P, int('P')},
        {VirtualKey::Q, int('Q')},
        {VirtualKey::R, int('R')},
        {VirtualKey::S, int('S')},
        {VirtualKey::T, int('T')},
        {VirtualKey::U, int('U')},
        {VirtualKey::V, int('V')},
        {VirtualKey::W, int('W')},
        {VirtualKey::X, int('X')},
        {VirtualKey::Y, int('Y')},
        {VirtualKey::Z, int('Z')},
        {VirtualKey::zero, int('0')},
        {VirtualKey::one, int('1')},
        {VirtualKey::two, int('2')},
        {VirtualKey::three, int('3')},
        {VirtualKey::four, int('4')},
        {VirtualKey::five, int('5')},
        {VirtualKey::six, int('6')},
        {VirtualKey::seven, int('7')},
        {VirtualKey::eight, int('8')},
        {VirtualKey::nine, int('9')}

    };
    return keycode_list;
}

std::string yougine::GetKeyName(VirtualKey key)
{
    switch (key)
    {
    case VirtualKey::MouseLeftClick: return "MouseLeftClick";
    case VirtualKey::MouseRightClick: return "MouseRightClick";
    case VirtualKey::MouseMiddleClick: return "MouseMiddleClick";
    case VirtualKey::Tab: return "Tab";
    case VirtualKey::Space: return "Space";
    case VirtualKey::LeftCtrl: return "LeftCtrl";
    case VirtualKey::RightCtrl: return "RightCtrl";
    case VirtualKey::Shift: return "Shift";
    case VirtualKey::LeftAlt: return "LeftAlt";
    case VirtualKey::RightAlt: return "RightAlt";
    case VirtualKey::Enter: return "Enter";
    case VirtualKey::Esc: return "Esc";
    case VirtualKey::At: return "At";
    case VirtualKey::LeftArrow: return "LeftArrow";
    case VirtualKey::RightArrow: return "RightArrow";
    case VirtualKey::UpperArrow: return "UpperArrow";
    case VirtualKey::DownArrow: return "DownArrow";
    case VirtualKey::A: return "A";
    case VirtualKey::B: return "B";
    case VirtualKey::C: return "C";
    case VirtualKey::D: return "D";
    case VirtualKey::E: return "E";
    case VirtualKey::F: return "F";
    case VirtualKey::G: return "G";
    case VirtualKey::H: return "H";
    case VirtualKey::I: return "I";
    case VirtualKey::J: return "J";
    case VirtualKey::K: return "K";
    case VirtualKey::L: return "L";
    case VirtualKey::M: return "M";
    case VirtualKey::N: return "N";
    case VirtualKey::O: return "O";
    case VirtualKey::P: return "P";
    case VirtualKey::Q: return "Q";
    case VirtualKey::R: return "R";
    case VirtualKey::S: return "S";
    case VirtualKey::T: return "T";
    case VirtualKey::U: return "U";
    case VirtualKey::V: return "V";
    case VirtualKey::W: return "W";
    case VirtualKey::X: return "X";
    case VirtualKey::Y: return "Y";
    case VirtualKey::Z: return "Z";
    case VirtualKey::zero: return "zero";
    case VirtualKey::one: return "one";
    case VirtualKey::two: return "two";
    case VirtualKey::three: return "three";
    case VirtualKey::four: return "four";
    case VirtualKey::five: return "five";
    case VirtualKey::six: return "six";
    case VirtualKey::seven: return "seven";
    case VirtualKey::eight: return "eight";
    case VirtualKey::nine: return "nine";
    default: return "Unknown";
    }
}
