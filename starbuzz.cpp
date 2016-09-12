/**
 * StarBuzz
 * Decorator pattern example
 */
#include <cstdio>
#include <memory>
#include <string>

class Beverage {
public:
  virtual ~Beverage() {}
  
  virtual std::string getDescription() {
    return description;
  }

  virtual double cost() = 0;

  std::string description { "Unknown description" };
};

class CondimentDecorator : public Beverage {
  virtual std::string getDescription() override = 0;
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
  Mocha(Beverage* beverage) : beverage(beverage) {}

  std::string getDescription() {
    return beverage->getDescription() + ", Mocha";
  }

  double cost() {
    return .20 + beverage->cost();
  }

private:
  std::unique_ptr<Beverage> beverage;
};

class Soy : public CondimentDecorator {
public:
  Soy(Beverage* beverage) : beverage(beverage) {}
  
  std::string getDescription() {
    return beverage->getDescription() + ", Soy";
  }

  double cost() {
    return .15 + beverage->cost();
  }

private:
  std::unique_ptr<Beverage> beverage;
};

class Whip : public CondimentDecorator {
public:
  Whip(Beverage* beverage) : beverage(beverage) {}

  std::string getDescription() {
    return beverage->getDescription() + ", Whip";
  }

  double cost() {
    return .10 + beverage->cost();
  }

private:
  std::unique_ptr<Beverage> beverage;
}; 

int main() {
  std::unique_ptr<Beverage> beverage { std::make_unique<Espresso>() };
  printf("%s $%f\n", beverage->getDescription().c_str(), beverage->cost());

  std::unique_ptr<Beverage> beverage2 { new Whip { new Mocha { new Mocha { new DarkRoast() }}}};
  printf("%s $%f\n", beverage2->getDescription().c_str(), beverage2->cost());

  std::unique_ptr<Beverage> beverage3 { new Whip { new Mocha { new Soy { new HouseBlend() }}}};
  printf("%s $%f\n", beverage3->getDescription().c_str(), beverage3->cost());
  return 0;
}
