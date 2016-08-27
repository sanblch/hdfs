/**
 * SimUDuck
 * Strategy pattern example
 */
#include <cstdio>

class FlyBehavior {

public:
  virtual void fly() = 0;
};


class FlyWithWings : public FlyBehavior {

public:
  void fly() {
    printf("I'm flying!\n");
  }
};


class FlyNoWay : public FlyBehavior {

public:
  void fly() {
    printf("I can't fly!\n");
  }
};

class FlyRocketPowered : public FlyBehavior {

public:
  void fly() {
    printf("I'm flying with a rocket!\n");
  }
};

class QuackBehavior {

public:
  virtual void quack() = 0;
};


class Quack : public QuackBehavior {

public:
  void quack() {
    printf("Quack!\n");
  }
};


class MuteQuack : public QuackBehavior {

public:
  void quack() {
    printf("<< Silence >>\n");
  }
};


class Squeak : public QuackBehavior {

public:
  void quack() {
    printf("Squeak!\n");
  }
};


class Duck {

public:
  ~Duck() {
    if(flyBehavior)
      delete flyBehavior;
    if(quackBehavior)
      delete quackBehavior;
  }
  
  virtual void display() = 0;

  void performFly() {
    flyBehavior->fly();
  }

  void performQuack() {
    quackBehavior->quack();
  }

  void setFlyBehavior(FlyBehavior* fb) {
    if(flyBehavior)
      delete flyBehavior;
    flyBehavior = fb;
  }

  void setQuackBehavior(QuackBehavior* qb) {
    if(quackBehavior)
      delete quackBehavior;
    quackBehavior = qb;
  }
  
  void swim() {
    printf("All ducks float, even decoys!\n");
  }

protected:
  FlyBehavior* flyBehavior;
  QuackBehavior* quackBehavior;
};


class MallardDuck : public Duck {

public:
  MallardDuck() {
    quackBehavior = new Quack();
    flyBehavior = new FlyWithWings();
  }

  void display() {
    printf("I'm a real Mallard duck.\n");
  }
};

class ModelDuck : public Duck {

public:
  ModelDuck() {
    flyBehavior = new FlyNoWay();
    quackBehavior = new Quack();
  }

  void display() {
    printf("I'm a model duck.\n");
  }
};

int main() {
  Duck* mallard = new MallardDuck();
  mallard->performFly();
  mallard->performQuack();

  Duck* model = new ModelDuck();
  model->performFly();
  model->setFlyBehavior(new FlyRocketPowered());
  model->performFly();

  delete mallard;
  delete model;
  
  return 0;
}
