/**
 * StarBuzz
 * Decorator pattern example
 */
#include <string>

class Beverage {
public:
  std::string getDescription() {
    return description;
  }

  virtual double cost() = 0;

  std::string description { "Unknown description" };
};

class CondimentDecorator : public Beverage {
  virtual std::string getDescription() = 0;
};

class Espresso : public Beverage {
public:
  Espresso() {
    description = "Espresso";
  }

  double cost() {
    return 1.99;
  }
};

class HouseBlend : public Beverage {
public:
  HouseBlend() {
    description = "House Blend Coffee";
  }

  double cost() {
    return 0.89;
  }
