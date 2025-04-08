#include <iostream>
#include <iomanip>
#include "engine.h"

int main() {
    // Создаем автомобиль с параметрами, похожими на реальные
    // Масса 1500 кг, мощность 100 кВт, Cd=0.3, Cr=0.01, радиус колеса 0.3 м
    Car car(1500.0f, 100000.0f, 0.3f, 0.01f, 0.3f);
    
    // Устанавливаем передаточное число (пример для 3-й передачи)
    car.setGearRatio(3.5f);
    
    // Симуляция на 10 секунд с шагом 0.1 секунды
    const float deltaTime = 0.1f;
    const float totalTime = 10.0f;
    
    std::cout << "Time(s)\tVelocity(km/h)\tAcceleration(m/s²)\tRPM\n";
    
    for (float time = 0; time <= totalTime; time += deltaTime) {
        // Управление автомобилем
        if (time < 3.0f) {
            // Разгон в течение 3 секунд
            car.setThrottle(0.8f);
            car.setBrake(0.0f);
        } else if (time < 6.0f) {
            // Движение с постоянной скоростью
            car.setThrottle(0.3f);
            car.setBrake(0.0f);
        } else {
            // Торможение
            car.setThrottle(0.0f);
            car.setBrake(0.5f);
        }
        
        // Обновляем состояние автомобиля
        car.update(deltaTime);
        
        // Выводим текущие параметры
        std::cout << std::fixed << std::setprecision(1);
        std::cout << time << "\t";
        std::cout << std::setprecision(2);
        std::cout << car.getVelocity() * 3.6f << "\t\t"; // Переводим м/с в км/ч
        std::cout << car.getAcceleration() << "\t\t\t";
        std::cout << car.getEngineRPM() << "\n";
    }
    
    return 0;
}