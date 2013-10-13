#ifndef CANMESSAGE_H
#define CANMESSAGE_H

#include <QByteArray>

class CanMessage
{
public:
    static int const ALL = 0x6010F;
    static int const FRONT_RIGHT = 0x60101;
    static int const FRONT_LEFT = 0x60102;
    static int const REAR_RIGHT = 0x60104;
    static int const REAR_LEFT = 0x60108;

    static int const FRONT = 0x60103;
    static int const REAR = 0x6010C;
    static int const LEFT = 0x6010A; //
    static int const RIGHT = 0x60105;

    static int const CLIGNO_ON = 0xC0;
    static int const CLIGNO_OFF = 0x40;
    static int const POS_ON = 0x20; //0x25;
    static int const POS_OFF = 0x10; //0x15;
    static int const CROIS_ON = 0x08;
    static int const CROIS_OFF = 0x15;
    static int const PHARE_ON = 0x02;
    static int const PHARE_OFF = 0x01;
    static int const STOP_ON = 0x02;
    static int const STOP_OFF = 0x01;
    static int const RECULE_ON = 0x08;
    static int const RECULE_OFF = 0x04;
    static int const ALL_OFF = 0x55;

    static int const LIGHT_UNCHANGED = 0;
    static int const LIGHT_OFF = 1;
    static int const LIGHT_ON = 2;
    static int const LIGHT_BLINKING =3;

    static int const ERROR_BATTERY_VOLTAGE = 0x4;
    static int const ERROR_FUSE = 0x8;
    static int const ERROR_MAINBEAM = 0x10;
    static int const ERROR_STOP_LIGHT = 0x10;
    static int const ERROR_LOWBEAM = 0x20;
    static int const ERROR_BACK_LIGHT = 0x20;
    static int const ERROR_POSITION_LIGHT = 0x40;
    static int const ERROR_BLINKER = 0x80;

    CanMessage(int p_id, int p_dataLow, int p_dataHigh);
    CanMessage(QByteArray p_byte);
    void setId(int id);
    int getId();
    void setDataLow(int p_dataLow);
    int getDataLow();
    void setDataHigh(int p_dataHigh);
    int getDataHigh();
    int getLightState(int p_light);
    void setLightState(int p_light, int p_state);
    bool isUseless();
    QByteArray getBytes();
    bool getError(int p_mask);

private:
    //static int const LIGHT[4] = {0, 2, 4, 6};
    //static int const LIGHT_MASK[4] = {0x3, 0xC, 0x30, 0xC0};

    int m_id, m_dataLow, m_dataHigh;
};

#endif // CANMESSAGE_H
