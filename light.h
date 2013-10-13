#ifndef LIGHT_H
#define LIGHT_H

class Light
{
public:
    static int const MAINBEAM = 0;
    static int const STOP_LIGHT = 0;
    static int const LOWBEAM = 1;
    static int const BACK_LIGHT = 1;
    static int const POSITION_LIGHT = 2;
    static int const BLINKER = 3;

    void setOn();
    void setOff();
    bool isOn();
    bool isOff();
    void toggle();
    int getKind();

protected:
    Light(int);

private:
    bool m_isOn;
    int  m_kind;
};

#endif // LIGHT_H
