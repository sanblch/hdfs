/**
 * StarBuzz
 * Decorator pattern example
 */
#include <cstdio>
#include <string>

class Beverage {
public:
  virtual ~Beverage() {}
  
  std::string getDescription() {
    return description;
  }

  virtual double cost() = 0;

  std::string description { "Unknown description" };
};

class CondimentDecorator : public virtual Beverage {
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
    return .89;
  }
};

class DarkRoast : public Beverage {
public:
  DarkRoast() {
    description = "Dark Roast Coffee";
  }

  double cost() {
    return .99;
  }
};

class Decaf : public Beverage {
public:
  Decaf() {
    description = "Decaf Coffee";
  }

  double cost() {
    return 1.05;
  }
};

class Mocha : public CondimentDecorator {
public:
  Mocha(Beverage* beverage) {
    this->beverage = beverage;
    printf("%s\n", beverage->getDescription().c_str());
  }

  ~Mocha() {
    delete beverage;
  }

  std::string getDescription() {
    printf("zvezda\n");
    return beverage->getDescription() + ", Mocha";
  }

  double cost() {
    return .20 + beverage->cost();
  }

private:
  Beverage* beverage;
};

class Soy : public CondimentDecorator {
public:
  Soy(Beverage* beverage) {
    this->beverage = beverage;
  }
  
  ~Soy() {
    delete beverage;
  }
  
  std::string getDescription() {
    return beverage->getDescription() + ", Soy";
  }

  double cost() {
    return .15 + beverage->cost();
  }

private:
  Beverage* beverage;
};

class Whip : public CondimentDecorator {
public:
  Whip(Beverage* beverage) {
    this->beverage = beverage;
  }

  ~Whip() {
    delete beverage;
  }

  std::string getDescription() {
    return beverage->getDescription() + ", Whip";
  }

  double cost() {
    return .10 + beverage->cost();
  }

private:
  Beverage* beverage;
}; 

int main() {
  Beverage* beverage = new Espresso();
  printf("%s $%f\n", beverage->getDescription().c_str(), beverage->cost());

  Beverage* beverage2 = new DarkRoast();
  beverage2 = new Mocha(beverage2);
  //beverage2 = new Mocha(beverage2);
  //beverage2 = new Whip(beverage2);
  printf("%s $%f\n", beverage2->getDescription().c_str(), beverage2->cost());
  return 0;
}
