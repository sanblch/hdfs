/**
 * StarBuzz
 * Decorator pattern example
 */
#include <cstdio>
#include <memory>
#include <string>

class Beverage {
public:
  enum Size {
    SMALL = -1,
    MEDIUM = 0,
    LARGE = 1
  };
  
  virtual ~Beverage() {}
  
  virtual std::string getDescription() {
    return description;
  }

  virtual double cost() = 0;

  virtual Size getSize() {
    return size;
  }
    
  virtual void setSize(Size size) {
    this->size = size;
  }

  std::string description { "Unknown description" };
  Size size { MEDIUM };
};

class CondimentDecorator : public Beverage {
public:
  CondimentDecorator(Beverage* beverage) : beverage(beverage) {};

  Beverage::Size getSize() {
    return beverage->getSize();
  }

  void setSize(Beverage::Size size) {
    beverage->setSize(size);
  }

protected:
  std::unique_ptr<Beverage> beverage;
};

class Espresso : public Beverage {
public:
  Espresso() {
    description = "Espresso";
  }

  double cost() {
    return 1.99 + .1 * getSize();
  }
};

class HouseBlend : public Beverage {
public:
  HouseBlend() {
    description = "House Blend Coffee";
  }

  double cost() {
    return .89 + .1 * getSize();
  }
};

class DarkRoast : public Beverage {
public:
  DarkRoast() {
    description = "Dark Roast Coffee";
  }

  double cost() {
    return .99 + .1 * getSize();
  }
};

class Decaf : public Beverage {
public:
  Decaf() {
    description = "Decaf Coffee";
  }

  double cost() {
    return 1.05 + .1 * getSize();
  }
};

class Mocha : public CondimentDecorator {
public:
  Mocha(Beverage* beverage) : CondimentDecorator(beverage) {}

  std::string getDescription() {
    return beverage->getDescription() + ", Mocha";
  }

  double cost() {
    return .20 + .05 * getSize() + beverage->cost();
  }
};

class Soy : public CondimentDecorator {
public:
  Soy(Beverage* beverage) : CondimentDecorator(beverage) {}
  
  std::string getDescription() {
    return beverage->getDescription() + ", Soy";
  }

  double cost() {
    return .15 + .05 * getSize() + beverage->cost();
  }
};

class Whip : public CondimentDecorator {
public:
  Whip(Beverage* beverage) : CondimentDecorator(beverage) {}

  std::string getDescription() {
    return beverage->getDescription() + ", Whip";
  }

  double cost() {
    return .10 + .05 * getSize() + beverage->cost();
  }
}; 

int main() {
  std::unique_ptr<Beverage> beverage { std::make_unique<Espresso>() };
  beverage->setSize(Beverage::MEDIUM);
  printf("%s $%f\n", beverage->getDescription().c_str(), beverage->cost());

  std::unique_ptr<Beverage> beverage2 { new Whip { new Mocha { new Mocha { new DarkRoast() }}}};
  beverage2->setSize(Beverage::LARGE);
  printf("%s $%f\n", beverage2->getDescription().c_str(), beverage2->cost());

  std::unique_ptr<Beverage> beverage3 { new Whip { new Mocha { new Soy { new HouseBlend() }}}};
  beverage3->setSize(Beverage::SMALL);
  printf("%s $%f\n", beverage3->getDescription().c_str(), beverage3->cost());
  return 0;
}
