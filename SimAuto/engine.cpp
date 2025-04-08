#include "engine.h"
#include <algorithm>

Car::Car(float mass, float maxPower, float dragCoeff, 
         float rollingResistance, float wheelRadius)
    : mass(mass), maxPower(maxPower), dragCoeff(dragCoeff),
      rollingResistance(rollingResistance), wheelRadius(wheelRadius),
      velocity(0), acceleration(0), throttle(0), brake(0),
      gearRatio(1), engineRPM(0) {}

void Car::setThrottle(float value) {
    throttle = std::clamp(value, 0.0f, 1.0f);
}

void Car::setBrake(float value) {
    brake = std::clamp(value, 0.0f, 1.0f);
}

void Car::setGearRatio(float ratio) {
    gearRatio = ratio;
}

void Car::update(float deltaTime) {
    // Рассчитываем все силы, действующие на автомобиль
    float engineForce = calculateEngineForce();
    float dragForce = calculateDragForce();
    float rollingForce = calculateRollingResistance();
    float brakingForce = calculateBrakingForce();
    
    // Суммарная сила (F = ma)
    float totalForce = engineForce - dragForce - rollingForce - brakingForce;
    
    // Ускорение (a = F/m)
    acceleration = totalForce / mass;
    
    // Обновляем скорость (v = v0 + a*dt)
    velocity += acceleration * deltaTime;
    
    // Не позволяем скорости стать отрицательной
    velocity = std::max(0.0f, velocity);
    
    // Обновляем RPM двигателя
    // Преобразуем линейную скорость в RPM: RPM = (v * gearRatio * 60) / (2 * π * wheelRadius)
    engineRPM = (velocity * gearRatio * 60.0f) / (2.0f * M_PI * wheelRadius);
}

float Car::getVelocity() const {
    return velocity;
}

float Car::getAcceleration() const {
    return acceleration;
}

float Car::getEngineRPM() const {
    return engineRPM;
}

float Car::calculateEngineForce() const {
    // Упрощенная модель: сила пропорциональна положению педали газа
    // В реальности нужно учитывать кривую мощности двигателя
    return throttle * maxPower / std::max(velocity, 0.1f); // P = F*v => F = P/v
}

float Car::calculateDragForce() const {
    // Аэродинамическое сопротивление: F = 0.5 * ρ * v² * Cd * A
    // Для упрощения объединим константы в dragCoeff
    return 0.5f * dragCoeff * velocity * velocity;
}

float Car::calculateRollingResistance() const {
    // Сопротивление качению: F = Cr * m * g
    return rollingResistance * mass * 9.81f;
}

float Car::calculateBrakingForce() const {
    // Тормозная сила пропорциональна положению педали тормоза
    // Максимальная тормозная сила обычно ограничена трением
    return brake * mass * 9.81f * 0.7f; // 0.7 - коэффициент трения
}