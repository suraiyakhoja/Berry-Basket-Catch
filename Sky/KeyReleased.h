#pragma once

namespace sk
{
    class KeyReleased
    {
    public:
        inline KeyReleased(int keyCode);

        inline int GetKeyCode() const;

    private:
        int mKeyCode;
    };
}
