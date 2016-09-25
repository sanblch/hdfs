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
  Ingredient(const std::) : name(str) {}
  
  virtual ~Ingredient() {};
  
  std::string getName() {
    return name;
  }
  
private:
  std::string name;
};

class Dough {};
class Sauce {};
class Veggie {};
class Cheese {};
class Pepperoni {};
class Clams {};

class ThinCrustDough : public Dough, public Ingredient {
public:
  ThinCrustDough() : Ingredient("thin crust dough") {}
};

class ThickCrustDough : public Dough, public Ingredient {
public:
  ThickCrustDough() : Ingredient("thick crust dough") {}
};

class MarinaraSauce : public Sauce, public Ingredient {
public:
  MarinaraSauce() : Ingredient("marinara sauce") {}
};

class PlumTomatoSauce : public Sauce, public Ingredient {
public:
  PlumTomatoSauce() : Ingredient("plum tomato sauce") {}
};

class Garlic : public Veggie, public Ingredient {
public:
  Garlic() : Ingredient("garlic") {}
};

class Onion : public Veggie, public Ingredient {
public:
  Onion() : Ingredient("onion") {}
};

class Mushroom : public Veggie, public Ingredient {
public:
  Mushroom() : Ingredient("mushroom") {}
};

class RedPepper : public Veggie, public Ingredient {
public:
  RedPepper() : Ingredient("red pepper") {}
};

class BlackOlives : public Veggie, public Ingredient {
public:
  BlackOlives() : Ingredient("black olives") {}
};

class EggPlant : public Veggie, public Ingredient {
public:
  EggPlant() : Ingredient("egg plant") {}
};

class Spinach : public Veggie, public Ingredient {
public:
  Spinach() : Ingredient("spinach") {}
};

class ReggianoCheese : public Cheese, public Ingredient {
public:
  ReggianoCheese() : Ingredient("reggiano cheese") {}
};

class MozzarellaCheese : public Cheese, public Ingredient {
public:
  MozzarellaCheese() : Ingredient("mozzarella cheese") {}
};

class SlicedPepperoni : public Pepperoni, public Ingredient {
public:
  SlicedPepperoni() : Ingredient("sliced pepperoni") {}
};

class FreshClams : public Clams, public Ingredient {
public:
  FreshClams() : Ingredient("fresh clams") {}
};

class FrozenClams : public Clams, public Ingredient {
public:
  FrozenClams() : Ingredient("frozen clams") {}
};

class Pizza {
public:
  virtual ~Pizza() {};
  
  virtual void prepare() = 0;

  void bake() {
    printf("Bake for 25 minutes at 350\n");
  }

  void cut() {
    printf("Cutting the pizza into diagonal slices\n");
  }

  void box() {
    printf("Place pizza in official PizzaStore box\n");
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

  virtual void toString() = 0;

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
    veggies.push_back(std::unique_ptr<Veggie>(new Garlic()));
    veggies.push_back(std::unique_ptr<Veggie>(new Onion()));
    veggies.push_back(std::unique_ptr<Veggie>(new Mushroom()));
    veggies.push_back(std::unique_ptr<Veggie>(new RedPepper()));
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
    veggies.push_back(std::unique_ptr<Veggie>(new BlackOlives()));
    veggies.push_back(std::unique_ptr<Veggie>(new EggPlant()));
    veggies.push_back(std::unique_ptr<Veggie>(new Spinach()));
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
    return getCheese()->toString() + " pizza on " + getDough()->toString() +
      " with " + getSauce()->toString();
  }
  
private:
  std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
};

class PepperoniPizza : public Pizza {
public:
  PepperoniPizza(PizzaIngredientFactory* ingredientFactory) : ingredientFactory(ingredientFactory) {}

  void prepare() {
    std::cout << "Preparing " << getName() << std::endl;
  }

  std::string toString() {
    return getPepperoni()->toString() + " pizza on " + getDough()->toString() +
      " with " + getSauce()->toString();
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
    return getClams()->toString() + " pizza on " + getDough()->toString() +
      " with " + getSauce()->toString() " and " + getCheese()->toString();
  }

private:
  std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
};

class VeggiePizza : public Pizza {
public:
  VeggiePizza(PizzaIngredientFactory* ingredientFactory) : ingredientFactory(ingredientFactory) {}

  void prepare() {
    std::cout << "Preparing " << getName() << std::endl;
  }

  std::string toString() {
    std::string str = "Veggie pizza on " + getDough()->toString() +
      " with " + getSauce()->toString() + ", " + getCheese()->toString();
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
  nyPizzaStore->orderPizza("cheese");
  return 0;
}
