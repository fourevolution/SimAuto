#ifndef ENGINE_H
#define ENGINE_H

#include <cmath>

class Car {
private:
    // Параметры автомобиля
    float mass;         // масса (кг)
    float maxPower;     // максимальная мощность двигателя (Вт)
    float dragCoeff;     // коэффициент аэродинамического сопротивления
    float rollingResistance; // коэффициент сопротивления качению
    float wheelRadius;   // радиус колеса (м)
    
    // Текущее состояние
    float velocity;      // текущая скорость (м/с)
    float acceleration;  // текущее ускорение (м/с²)
    float throttle;      // положение педали газа (0..1)
    float brake;         // положение педали тормоза (0..1)
    float gearRatio;     // передаточное число текущей передачи
    float engineRPM;     // текущие обороты двигателя (об/мин)
    
public:
    Car(float mass, float maxPower, float dragCoeff, 
        float rollingResistance, float wheelRadius);
        
    // Управление автомобилем
    void setThrottle(float value);
    void setBrake(float value);
    void setGearRatio(float ratio);
    
    // Обновление физического состояния
    void update(float deltaTime);
    
    // Получение текущих параметров
    float getVelocity() const;
    float getAcceleration() const;
    float getEngineRPM() const;
    
private:
    // Вспомогательные методы
    float calculateEngineForce() const;
    float calculateDragForce() const;
    float calculateRollingResistance() const;
    float calculateBrakingForce() const;
};

#endif // ENGINE_H