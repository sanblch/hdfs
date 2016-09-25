/**
 * PizzaStore
 * Factory pattern example
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Ingredient {
public:
  Ingredient(const char* str) : name(str) {}
  
  virtual ~Ingredient() {};
  
  const std::string toString() {
    return std::string(name);
  }
  
private:
  const char* name;
};

class Dough : public Ingredient {
public:
  Dough(const char* str) : Ingredient(str) {}
};

class Sauce : public Ingredient {
public:
  Sauce(const char* str) : Ingredient(str) {}
};

class Veggie : public Ingredient {
public:
  Veggie(const char* str) : Ingredient(str) {}
};

class Cheese : public Ingredient {
public:
  Cheese(const char* str) : Ingredient(str) {}
};

class Pepperoni : public Ingredient {
public:
  Pepperoni(const char* str) : Ingredient(str) {}
};

class Clams : public Ingredient {
public:
  Clams(const char* str) : Ingredient(str) {}
};

class ThinCrustDough : public Dough {
public:
  ThinCrustDough() : Dough("thin crust dough") {}
};

class ThickCrustDough : public Dough {
public:
  ThickCrustDough() : Dough("thick crust dough") {}
};

class MarinaraSauce : public Sauce {
public:
  MarinaraSauce() : Sauce("marinara sauce") {}
};

class PlumTomatoSauce : public Sauce {
public:
  PlumTomatoSauce() : Sauce("plum tomato sauce") {}
};

class Garlic : public Veggie {
public:
  Garlic() : Veggie("garlic") {}
};

class Onion : public Veggie {
public:
  Onion() : Veggie("onion") {}
};

class Mushroom : public Veggie {
public:
  Mushroom() : Veggie("mushroom") {}
};

class RedPepper : public Veggie {
public:
  RedPepper() : Veggie("red pepper") {}
};

class BlackOlives : public Veggie {
public:
  BlackOlives() : Veggie("black olives") {}
};

class EggPlant : public Veggie {
public:
  EggPlant() : Veggie("egg plant") {}
};

class Spinach : public Veggie {
public:
  Spinach() : Veggie("spinach") {}
};

class ReggianoCheese : public Cheese {
public:
  ReggianoCheese() : Cheese("reggiano cheese") {}
};

class MozzarellaCheese : public Cheese {
public:
  MozzarellaCheese() : Cheese("mozzarella cheese") {}
};

class SlicedPepperoni : public Pepperoni {
public:
  SlicedPepperoni() : Pepperoni("sliced pepperoni") {}
};

class FreshClams : public Clams {
public:
  FreshClams() : Clams("fresh clams") {}
};

class FrozenClams : public Clams {
public:
  FrozenClams() : Clams("frozen clams") {}
};

class Pizza {
public:
  virtual ~Pizza() {};
  
  virtual void prepare() = 0;

  virtual void bake() {
    std::cout << "Bake for 25 minutes at 350" << std::endl;
  }

  virtual void cut() {
    std::cout << "Cutting the pizza into diagonal slices" << std::endl;
  }

  virtual void box() {
    std::cout << "Place pizza in official PizzaStore box" << std::endl;
  }

  std::string getName() {
    return name;
  }

  void setName(const std::string& name) {
    this->name = name;
  }

  Dough* getDough() {
    return dough.get();
  }

  void setDough(Dough* dough) {
    this->dough = std::unique_ptr<Dough>(dough);
  }

  Sauce* getSauce() {
    return sauce.get();
  }

  void setSauce(Sauce* sauce) {
    this->sauce = std::unique_ptr<Sauce>(sauce);
  }

  Cheese* getCheese() {
    return cheese.get();
  }

  void setCheese(Cheese* cheese) {
    this->cheese = std::unique_ptr<Cheese>(cheese);
  }

  Pepperoni* getPepperoni() {
    return pepperoni.get();
  }

  void setPepperoni(Pepperoni* pepperoni) {
    this->pepperoni = std::unique_ptr<Pepperoni>(pepperoni);
  }

  Clams* getClams() {
    return clams.get();
  }

  void setClams(Clams* clams) {
    this->clams = std::unique_ptr<Clams>(clams);
  }

  std::vector<std::unique_ptr<Veggie> >& getVeggies() {
    return veggies;
  }

  void setVeggies(std::vector<std::unique_ptr<Veggie> > veggies) {
    this->veggies = std::move(veggies);
  }

  virtual std::string toString() = 0;

private:
  std::string name;
  std::unique_ptr<Dough> dough;
  std::unique_ptr<Sauce> sauce;
  std::vector<std::unique_ptr<Veggie> > veggies;
  std::unique_ptr<Cheese> cheese;
  std::unique_ptr<Pepperoni> pepperoni;
  std::unique_ptr<Clams> clams;
};

class PizzaIngredientFactory {
public:
  virtual Dough* createDough() = 0;
  virtual Sauce* createSauce() = 0;
  virtual Cheese* createCheese() = 0;
  virtual std::vector<std::unique_ptr<Veggie> > createVeggies() = 0;
  virtual Pepperoni* createPepperoni() = 0;
  virtual Clams* createClams() = 0;
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory {
public:
  Dough* createDough() {
    return new ThinCrustDough();
  }

  Sauce* createSauce() {
    return new MarinaraSauce();
  }

  Cheese* createCheese() {
    return new ReggianoCheese();
  }

  std::vector<std::unique_ptr<Veggie> > createVeggies() {
    std::vector<std::unique_ptr<Veggie> > veggies;
    veggies.emplace_back(new Garlic());
    veggies.emplace_back(new Onion());
    veggies.emplace_back(new Mushroom());
    veggies.emplace_back(new RedPepper());
    return veggies;
  }

  Pepperoni* createPepperoni() {
    return new SlicedPepperoni();
  }

  Clams* createClams() {
    return new FreshClams();
  }
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory {
public:
  Dough* createDough() {
    return new ThickCrustDough();
  }

  Sauce* createSauce() {
    return new PlumTomatoSauce();
  }

  Cheese* createCheese() {
    return new MozzarellaCheese();
  }

  std::vector<std::unique_ptr<Veggie> > createVeggies() {
    std::vector<std::unique_ptr<Veggie> > veggies;
    veggies.emplace_back(new BlackOlives());
    veggies.emplace_back(new EggPlant());
    veggies.emplace_back(new Spinach());
    return veggies;
  }

  Pepperoni* createPepperoni() {
    return new SlicedPepperoni();
  }

  Clams* createClams() {
    return new FrozenClams();
  }
};
  
class CheesePizza : public Pizza {
public:
  CheesePizza(PizzaIngredientFactory* ingredientFactory) : ingredientFactory(ingredientFactory) {}

  void prepare() {
    std::cout << "Preparing " << getName() << std::endl;
    setDough(ingredientFactory->createDough());
    setSauce(ingredientFactory->createSauce());
    setCheese(ingredientFactory->createCheese());
  }

  std::string toString() {
    return std::string("The pizza is a ") + getCheese()->toString() + std::string(" pizza on ") +
    getDough()->toString() + std::string(" with ") + getSauce()->toString();
  }
  
private:
  std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
};

class PepperoniPizza : public Pizza {
public:
  PepperoniPizza(PizzaIngredientFactory* ingredientFactory) : ingredientFactory(ingredientFactory) {}

  void prepare() {
    std::cout << "Preparing " << getName() << std::endl;
    setDough(ingredientFactory->createDough());
    setSauce(ingredientFactory->createSauce());
    setCheese(ingredientFactory->createCheese());
    setPepperoni(ingredientFactory->createPepperoni());
  }

  std::string toString() {
    return std::string("The pizza is a ") + getPepperoni()->toString() +
      std::string(" pizza on ") + getDough()->toString() + std::string(" with ") +
      getSauce()->toString() + std::string(" and ") + getCheese()->toString();
  }

private:
  std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
};

class ClamPizza : public Pizza {
public:
  ClamPizza(PizzaIngredientFactory* ingredientFactory) : ingredientFactory(ingredientFactory) {}

  void prepare() {
    std::cout << "Preparing " << getName() << std::endl;
    setDough(ingredientFactory->createDough());
    setSauce(ingredientFactory->createSauce());
    setCheese(ingredientFactory->createCheese());
    setClams(ingredientFactory->createClams());
  }

  std::string toString() {
    return std::string("The pizza is a ") + getClams()->toString() + std::string(" pizza on ") +
    getDough()->toString() +  std::string(" with ") + getSauce()->toString() +
    std::string(" and ") + getCheese()->toString();
  }

private:
  std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
};

class VeggiePizza : public Pizza {
public:
  VeggiePizza(PizzaIngredientFactory* ingredientFactory) : ingredientFactory(ingredientFactory) {}

  void prepare() {
    std::cout << "Preparing " << getName() << std::endl;
    setDough(ingredientFactory->createDough());
    setSauce(ingredientFactory->createSauce());
    setVeggies(ingredientFactory->createVeggies());
  }

  std::string toString() {
    std::string str = std::string("The pizza is a veggie pizza on ") + getDough()->toString() +
      std::string(" with ") + getSauce()->toString();
    for(auto& veggie : getVeggies()) {
      str += std::string(", ") + veggie->toString();
    }
    return str;
  }

private:
  std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
};


class PizzaStore {
public:
  std::shared_ptr<Pizza> orderPizza(const std::string& type) {
    auto pizza = std::shared_ptr<Pizza>(createPizza(type));
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
  }
protected:
  virtual Pizza* createPizza(const std::string& type) = 0;
};

class NYPizzaStore : public PizzaStore {
private:
  Pizza* createPizza(const std::string& type) {
    Pizza* pizza = nullptr;
    auto ingredientFactory = new NYPizzaIngredientFactory();
    if(type == "cheese") {
      pizza = new CheesePizza(ingredientFactory);
      pizza->setName("New York Style Cheese Pizza");
    } else if(type == "veggie") {
      pizza = new VeggiePizza(ingredientFactory);
      pizza->setName("New York Style Veggie Pizza");
    } else if(type == "clam") {
      pizza = new ClamPizza(ingredientFactory);
      pizza->setName("New York Style Clam Pizza");
    } else if(type == "pepperoni") {
      pizza = new PepperoniPizza(ingredientFactory);
      pizza->setName("New York Style Pepperoni Pizza");
    }
    return pizza;
  }
};

class ChicagoPizzaStore : public PizzaStore {
private:
  Pizza* createPizza(const std::string& type) {
    Pizza* pizza = nullptr;
    auto ingredientFactory = new ChicagoPizzaIngredientFactory();
    if(type == "cheese") {
      pizza = new CheesePizza(ingredientFactory);
      pizza->setName("Chicago Style Cheese Pizza");
    } else if(type == "veggie") {
      pizza = new VeggiePizza(ingredientFactory);
      pizza->setName("Chicago Style Veggie Pizza");
    } else if(type == "clam") {
      pizza = new ClamPizza(ingredientFactory);
      pizza->setName("Chicago Style Clam Pizza");
    } else if(type == "pepperoni") {
      pizza = new PepperoniPizza(ingredientFactory);
      pizza->setName("Chicago Style Pepperoni Pizza");
    }
    return pizza;
  }
};

int main() {
  auto nyPizzaStore = std::unique_ptr<PizzaStore>(new NYPizzaStore());
  auto nyCheesePizza = nyPizzaStore->orderPizza("cheese");
  std::cout << nyCheesePizza->toString() << std::endl;

  auto nyVeggiePizza = nyPizzaStore->orderPizza("veggie");
  std::cout << nyVeggiePizza->toString() << std::endl;

  auto chicagoPizzaStore = std::unique_ptr<PizzaStore>(new ChicagoPizzaStore());
  auto chicagoClamPizza = chicagoPizzaStore->orderPizza("clam");
  std::cout << chicagoClamPizza->toString() << std::endl;
  return 0;
}
