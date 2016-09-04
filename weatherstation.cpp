/**
 * WeatherStation
 * Observer pattern example
 */
#include <cstdio>
#include <list>

class Observable;

class Observer {
public:
  virtual ~Observer() {}
  virtual void update(Observable* observable) = 0;
};

class Observable {
public:
  virtual ~Observable() {
    for(auto it = observers.begin(); it != observers.end(); ++it)
      delete *it;
  }
  
  void addObserver(Observer* o) {
    observers.push_back(o);
  }
  
  void removeObserver(Observer* o) {
    observers.remove(o);
  }
  
  void notifyObservers() {
    if(changed)
      for(auto it = observers.begin(); it != observers.end(); ++it)
        (*it)->update(this);
    changed = false;
  }

  void setChanged() {
    changed = true;
  }
  
private:
  std::list<Observer*> observers;
  bool changed;
};

class DisplayElement {
public:
  virtual void display() = 0;
};

class WeatherData : public Observable {
public:
  void measurementsChanged() {
    setChanged();
    notifyObservers();
  }

  void setMeasurements(float temperature, float humidity, float pressure) {
    this->temperature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;
    measurementsChanged();
  }

  float getTemperature() {
    return temperature;
  }

  float getHumidity() {
    return humidity;
  }

  float getPressure() {
    return pressure;
  }

private:
  float temperature;
  float humidity;
  float pressure;
};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
public:
  void update(Observable* observable) {
    if(WeatherData* weatherData = dynamic_cast<WeatherData*>(observable)) {
      this->temperature = weatherData->getTemperature();
      this->humidity = weatherData->getHumidity();
      display();
    }
  }

  void display() {
    printf("Current conditions: %.2fF degrees and %.2f%% humidity\n", temperature, humidity);
  }

private:
  float temperature;
  float humidity;
};

class HeatIndexDisplay : public Observer, public DisplayElement {
public:
  void update(Observable* observable) {
    if(WeatherData* weatherData = dynamic_cast<WeatherData*>(observable)) {
      this->temperature = weatherData->getTemperature();
      this->humidity = weatherData->getHumidity();
      display();
    }
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
};

class ForecastDisplay : public Observer, public DisplayElement {
public:
  void update(Observable* observable) {
    if(WeatherData* weatherData = dynamic_cast<WeatherData*>(observable)) {
      lastPressure = currentPressure;
      currentPressure = weatherData->getPressure();
      display();
    }
  }

  void display() {
    float delta = (lastPressure - currentPressure) / currentPressure * 100;
    if(delta < -1)
      printf("Forecast: Watch out for cooler, rainy weather\n");
    else if(delta > 1)
      printf("Forecast: Improving weather on the way!\n");
    else
      printf("Forecast: More of the same\n");
  }
  
private:
  float currentPressure { 29.92 };
  float lastPressure;
};

int main() {
  WeatherData* weatherData = new WeatherData();
  weatherData->addObserver(new CurrentConditionsDisplay());
  weatherData->addObserver(new HeatIndexDisplay());
  weatherData->addObserver(new ForecastDisplay());
  
  weatherData->setMeasurements(80.0, 65.0, 30.4);
  weatherData->setMeasurements(82.0, 70.0, 29.2);
  weatherData->setMeasurements(78.0, 90.0, 29.2);

  delete weatherData;
  
  return 0;
}
