/**
 * WeatherStation
 * Observer pattern example
 */
#include <cstdio>
#include <list>

class Observer {
public:
  virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject {
public:
  virtual void registerObserver(Observer* o) = 0;
  virtual void removeObserver(Observer* o) = 0;
  virtual void notifyObservers() = 0;
};

class DisplayElement {
public:
  virtual void display() = 0;
};

class WeatherData : public Subject {
public:
  void registerObserver(Observer* o) {
    observers.push_back(o);
  }

  void removeObserver(Observer* o) {
    observers.remove(o);
  }

  void notifyObservers() {
    for(auto it = observers.begin(); it != observers.end(); ++it) {
      (*it)->update(temperature, humidity, pressure);
    }
  }

  void measurementsChanged() {
    notifyObservers();
  }

  void setMeasurements(float temperature, float humidity, float pressure) {
    this->temperature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;
    measurementsChanged();
  }

private:
  std::list<Observer*> observers;
  float temperature;
  float humidity;
  float pressure;
};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
public:
  CurrentConditionsDisplay(Subject* weatherData) {
    this->weatherData = weatherData;
    weatherData->registerObserver(this);
  }

  void update(float temperature, float humidity, float) {
    this->temperature = temperature;
    this->humidity = humidity;
    display();
  }

  void display() {
    printf("Current conditions: %.2fF degrees and %.2f%% humidity\n", temperature, humidity);
  }

private:
  float temperature;
  float humidity;
  Subject* weatherData;
};

int main() {
  WeatherData* weatherData = new WeatherData();
  CurrentConditionsDisplay* currentDisplay = new CurrentConditionsDisplay(weatherData);

  weatherData->setMeasurements(80.0, 65.0, 30.4);
  weatherData->setMeasurements(82.0, 70.0, 29.2);
  weatherData->setMeasurements(78.0, 90.0, 29.2);

  delete weatherData;
  delete currentDisplay;
  
  return 0;
}
