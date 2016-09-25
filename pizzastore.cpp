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
  Ingredient(const std::string& str) : name(str) {}
  
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

  void setName(const std::string& name) {
    this->name = name;
  }

  void setDough(Dough* dough) {
    this->dough = dough;
  }

  void setSauce(Sauce* sauce) {
    this->sauce = std::unique_ptr<Sauce>(sauce);
  }

  void setCheese(Cheese* cheese) {
    this->cheese = std::unique_ptr<Cheese>(cheese);
  }

  void setPepperoni(Pepperoni* pepperoni) {
    this->pepperoni = std::unique_ptr<Pepperoni>(pepperoni);
  }

  void setClams(Clams* clams) {
    this->clams = std::unique_ptr<Clams>(clams);
  }

  std::string getName() {
    return name;
  }

protected:
  Dough* dough;

private:
  std::string name;
  std::unique_ptr<Sauce> sauce;
  std::vector<std::unique_ptr<Veggie> > veggies;
  std::unique_ptr<Cheese> cheese;
  std::unique_ptr<Pepperoni> pepperoni;
  std::unique_ptr<Clams> clams;
};

class PizzaIngredientFactory {
public:
  virtual Dough* createDough() {}
  virtual Sauce* createSauce() {}
  virtual Cheese* createCheese() {}
  virtual std::vector<std::unique_ptr<Veggie> > createVeggies() = 0;
  virtual Pepperoni* createPepperoni() = 0;
  virtual Clams* createClams() {}
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory {
public:
  virtual Dough* createDough() {
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
  CheesePizza(PizzaIngredientFactory* ingredientFactory) {
    this->ingredientFactory = ingredientFactory;
  }

  void prepare() {
    printf("Preparing %s\n", getName().c_str());
    dough = ingredientFactory->createDough();
    std::cout << ingredientFactory << std::endl;
    setSauce(ingredientFactory->createSauce());
    setCheese(ingredientFactory->createCheese());
    std::cout << ingredientFactory << std::endl;
  }
  
private:
  PizzaIngredientFactory* ingredientFactory;
};

class PepperoniPizza : public Pizza {
public:
  PepperoniPizza(PizzaIngredientFactory* ingredientFactory) {
    this->ingredientFactory = ingredientFactory;
  }

  void prepare() {
    printf("Preparing %s\n", getName().c_str());
  }

private:
  PizzaIngredientFactory* ingredientFactory;
};

class ClamPizza : public Pizza {
public:
  ClamPizza(PizzaIngredientFactory* ingredientFactory) {
    this->ingredientFactory = ingredientFactory;
  };

  void prepare() {
    printf("Preparing %s\n", getName().c_str());
    setDough(ingredientFactory->createDough());
    setSauce(ingredientFactory->createSauce());
    setCheese(ingredientFactory->createCheese());
    setClams(ingredientFactory->createClams());
  }

private:
  PizzaIngredientFactory* ingredientFactory;
};

class VeggiePizza : public Pizza {
public:
  VeggiePizza(PizzaIngredientFactory* ingredientFactory) {
    this->ingredientFactory = ingredientFactory;
  }

  void prepare() {
    printf("Preparing %s\n", getName().c_str());
  }

private:
  PizzaIngredientFactory* ingredientFactory;
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
    auto ingredientFactory = std::shared_ptr<PizzaIngredientFactory>(new NYPizzaIngredientFactory());
    if(type == "cheese") {
      pizza = new CheesePizza(ingredientFactory.get());
      pizza->setName("New York Style Cheese Pizza");
    } else if(type == "veggie") {
      pizza = new VeggiePizza(ingredientFactory.get());
      pizza->setName("New York Style Veggie Pizza");
    } else if(type == "clam") {
      pizza = new ClamPizza(ingredientFactory.get());
      pizza->setName("New York Style Clam Pizza");
    } else if(type == "pepperoni") {
      pizza = new PepperoniPizza(ingredientFactory.get());
      pizza->setName("New York Style Pepperoni Pizza");
    }
    return pizza;
  }
};

class ChicagoPizzaStore : public PizzaStore {
private:
  Pizza* createPizza(const std::string& type) {
    Pizza* pizza = nullptr;
    auto ingredientFactory = std::shared_ptr<PizzaIngredientFactory>(new ChicagoPizzaIngredientFactory());
    if(type == "cheese") {
      pizza = new CheesePizza(ingredientFactory.get());
      pizza->setName("Chicago Style Cheese Pizza");
    } else if(type == "veggie") {
      pizza = new VeggiePizza(ingredientFactory.get());
      pizza->setName("Chicago Style Veggie Pizza");
    } else if(type == "clam") {
      pizza = new ClamPizza(ingredientFactory.get());
      pizza->setName("Chicago Style Clam Pizza");
    } else if(type == "pepperoni") {
      pizza = new PepperoniPizza(ingredientFactory.get());
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
