#pragma once

namespace sk
{
    class KeyPressed
    {
    public:
        inline KeyPressed(int keyCode);

        inline int GetKeyCode() const;

    private:
        int mKeyCode;
    };
}

