#ifndef PHOTORESISTORCONTROL_H
#define PHOTORESISTORCONTROL_H

class PhotoresistorControl {
private:
    int photoresistorPin;
    int lightThreshold;
    int lightLevel;

public:
    PhotoresistorControl(int pin, int threshold = 512);

    void readLightLevel();
    int getLightLevel() const;
    bool isLightBelowThreshold() const;
    void setThreshold(int threshold);
};

#endif // PHOTORESISTORCONTROL_H
