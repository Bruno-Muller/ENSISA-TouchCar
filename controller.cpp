#include "controller.h"

Controller::Controller(Car * p_model, MainWindow * p_view)
{
    this->m_model = p_model;
    this->m_view = p_view;

    this->m_server = new Server(m_view, this);

    connect(&(this->m_timer), SIGNAL(timeout()), this, SLOT(blinkerTask()) );

}

Controller::~Controller()
{
    delete this->m_server;
}

void Controller::blinkerTask()
{
    bool repaint(false);
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (this->m_model->getLightState(i, j) == CanMessage::LIGHT_BLINKING) {
                this->m_model->getLight(i, j)->toggle();
                repaint = true;
            }
    if (repaint)
        this->m_view->updateIcons();
}

Controller::BlinkerState Controller::getBlinkerState()
{
    if (((this->m_model->getLightState(OpticalBlock::FRONT_LEFT, Light::BLINKER) == CanMessage::LIGHT_BLINKING) ||
         (this->m_model->getLightState(OpticalBlock::REAR_LEFT, Light::BLINKER) == CanMessage::LIGHT_BLINKING)) &&
            ((this->m_model->getLightState(OpticalBlock::FRONT_RIGHT, Light::BLINKER) == CanMessage::LIGHT_BLINKING) ||
             (this->m_model->getLightState(OpticalBlock::REAR_RIGHT, Light::BLINKER) == CanMessage::LIGHT_BLINKING)))
        return BlinkerState(BOTH);
    if (((this->m_model->getLightState(OpticalBlock::FRONT_LEFT, Light::BLINKER) == CanMessage::LIGHT_BLINKING) ||
         (this->m_model->getLightState(OpticalBlock::REAR_LEFT, Light::BLINKER) == CanMessage::LIGHT_BLINKING)) &&
            (this->m_model->getLightState(OpticalBlock::FRONT_RIGHT, Light::BLINKER) != CanMessage::LIGHT_BLINKING) &&
            (this->m_model->getLightState(OpticalBlock::REAR_RIGHT, Light::BLINKER) != CanMessage::LIGHT_BLINKING))
        return BlinkerState(LEFT);
    if (((this->m_model->getLightState(OpticalBlock::FRONT_RIGHT, Light::BLINKER) == CanMessage::LIGHT_BLINKING) ||
         (this->m_model->getLightState(OpticalBlock::REAR_RIGHT, Light::BLINKER) == CanMessage::LIGHT_BLINKING)) &&
            (this->m_model->getLightState(OpticalBlock::REAR_LEFT, Light::BLINKER) != CanMessage::LIGHT_BLINKING) &&
            (this->m_model->getLightState(OpticalBlock::REAR_LEFT, Light::BLINKER) != CanMessage::LIGHT_BLINKING))
        return BlinkerState(RIGHT);
    return BlinkerState(OFF);
}

void Controller::acceptCanMessage(CanMessage p_canMessage)
{
    this->m_model->acceptCanMessage(p_canMessage);

    if (p_canMessage.getLightState(Light::BLINKER) == CanMessage::LIGHT_BLINKING)
        this->m_timer.start(500);
    else if (p_canMessage.getLightState(Light::BLINKER) == CanMessage::LIGHT_OFF)
        this->m_timer.stop();

    this->m_view->updateIcons();
}

void Controller::toggleLeftBlinker()
{
    BlinkerState blinkerState = this->getBlinkerState();
    this->m_server->sendToAll(CanMessage(CanMessage::ALL, CanMessage::CLIGNO_OFF, 0));
    if (blinkerState != BlinkerState(LEFT))
        this->m_server->sendToAll(CanMessage(CanMessage::LEFT, CanMessage::CLIGNO_ON, 0));
}

void Controller::toggleRightBlinker()
{
    BlinkerState blinkerState = this->getBlinkerState();
    this->m_server->sendToAll(CanMessage(CanMessage::ALL, CanMessage::CLIGNO_OFF, 0));
    if (blinkerState != BlinkerState(RIGHT))
        this->m_server->sendToAll(CanMessage(CanMessage::RIGHT, CanMessage::CLIGNO_ON, 0));
}

void Controller::toggleWarning()
{
    BlinkerState blinkerState = this->getBlinkerState();
    this->m_server->sendToAll(CanMessage(CanMessage::ALL, CanMessage::CLIGNO_OFF, 0));
    if (blinkerState != BlinkerState(BOTH))
        this->m_server->sendToAll(CanMessage(CanMessage::ALL, CanMessage::CLIGNO_ON, 0));
}

void Controller::toggleStopLight()
{
    if ((this->m_model->getLightState(OpticalBlock::REAR_LEFT, Light::STOP_LIGHT) == CanMessage::LIGHT_ON) ||
            (this->m_model->getLightState(OpticalBlock::REAR_RIGHT, Light::STOP_LIGHT) == CanMessage::LIGHT_ON))
        this->m_server->sendToAll(CanMessage(CanMessage::REAR, CanMessage::STOP_OFF, 0));
    else
        this->m_server->sendToAll(CanMessage(CanMessage::REAR, CanMessage::STOP_ON, 0));
}

void Controller::toggleBackLight()
{
    if ((this->m_model->getLightState(OpticalBlock::REAR_LEFT, Light::BACK_LIGHT) == CanMessage::LIGHT_ON) ||
            (this->m_model->getLightState(OpticalBlock::REAR_RIGHT, Light::BACK_LIGHT) == CanMessage::LIGHT_ON))
        this->m_server->sendToAll(CanMessage(CanMessage::REAR, CanMessage::RECULE_OFF, 0));
    else
        this->m_server->sendToAll(CanMessage(CanMessage::REAR, CanMessage::RECULE_ON, 0));

}

void Controller::toggleMainBeam()
{
    if ((this->m_model->getLightState(OpticalBlock::FRONT_LEFT, Light::MAINBEAM) == CanMessage::LIGHT_ON) ||
            (this->m_model->getLightState(OpticalBlock::FRONT_RIGHT, Light::MAINBEAM) == CanMessage::LIGHT_ON))
        this->m_server->sendToAll(CanMessage(CanMessage::FRONT, CanMessage::PHARE_OFF, 0));
    else
        this->m_server->sendToAll(CanMessage(CanMessage::FRONT, CanMessage::PHARE_ON, 0));
}

void Controller::toggleLowBeamPositionLight()
{
    // OFF -> Position
    if ((this->m_model->getLightState(OpticalBlock::FRONT_LEFT, Light::POSITION_LIGHT) == CanMessage::LIGHT_OFF) ||
            (this->m_model->getLightState(OpticalBlock::FRONT_RIGHT, Light::POSITION_LIGHT) == CanMessage::LIGHT_OFF) ||
            (this->m_model->getLightState(OpticalBlock::REAR_LEFT, Light::POSITION_LIGHT) == CanMessage::LIGHT_OFF) ||
            (this->m_model->getLightState(OpticalBlock::REAR_RIGHT, Light::POSITION_LIGHT) == CanMessage::LIGHT_OFF))
        this->m_server->sendToAll(CanMessage(CanMessage::ALL, CanMessage::POS_ON, 0));


    // Position LowBeam -> OFF
    else if ((this->m_model->getLightState(OpticalBlock::FRONT_LEFT, Light::LOWBEAM) == CanMessage::LIGHT_ON) ||
             (this->m_model->getLightState(OpticalBlock::FRONT_RIGHT, Light::LOWBEAM) == CanMessage::LIGHT_ON)) {
        this->m_server->sendToAll(CanMessage(CanMessage::ALL, CanMessage::POS_OFF, 0));
        this->m_server->sendToAll(CanMessage(CanMessage::FRONT, CanMessage::CROIS_OFF, 0));
    }
    // Position -> Position LowBeam
    else if ((this->m_model->getLightState(OpticalBlock::FRONT_LEFT, Light::POSITION_LIGHT) == CanMessage::LIGHT_ON) ||
             (this->m_model->getLightState(OpticalBlock::FRONT_RIGHT, Light::POSITION_LIGHT) == CanMessage::LIGHT_ON) ||
             (this->m_model->getLightState(OpticalBlock::REAR_LEFT, Light::POSITION_LIGHT) == CanMessage::LIGHT_ON) ||
             (this->m_model->getLightState(OpticalBlock::REAR_RIGHT, Light::POSITION_LIGHT) == CanMessage::LIGHT_ON))
        this->m_server->sendToAll(CanMessage(CanMessage::FRONT, CanMessage::CROIS_ON, 0));
}
