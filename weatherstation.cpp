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

class HeatIndexDisplay : public Observer, public DisplayElement {
public:
  HeatIndexDisplay(Subject* weatherData) {
    this->weatherData = weatherData;
    weatherData->registerObserver(this);
  }

  void update(float temperature, float humidity, float) {
    this->temperature = temperature;
    this->humidity = humidity;
    display();
  }

  void display() {
    printf("Heat index is %.5f\n", computeHeatIndex(temperature, humidity));
  }

private:
  float computeHeatIndex(float t, float rh) {
    return ((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh) +
    (0.00941695 * (t * t)) + (0.00728898 * (rh * rh)) +
    (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
    (0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *  
    (rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
    (0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +     
    0.000000000843296 * (t * t * rh * rh * rh)) -
    (0.0000000000481975 * (t * t * t * rh * rh * rh)));
  }
  float temperature;
  float humidity;
  Subject* weatherData;
};

int main() {
  WeatherData* weatherData = new WeatherData();
  CurrentConditionsDisplay* currentDisplay = new CurrentConditionsDisplay(weatherData);
  HeatIndexDisplay* heatIndexDisplay = new HeatIndexDisplay(weatherData);

  weatherData->setMeasurements(80.0, 65.0, 30.4);
  weatherData->setMeasurements(82.0, 70.0, 29.2);
  weatherData->setMeasurements(78.0, 90.0, 29.2);

  delete weatherData;
  delete currentDisplay;
  delete heatIndexDisplay;
  
  return 0;
}
