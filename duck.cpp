#include <cstdio>

class FlyBehavior {

public:
  virtual void fly();
};


class FlyWithWings : FlyBehavior {

public:
  void fly() {
    printf("I'm flying!\n");
  }
};


class FlyNoWay : FlyBehavior {

public:
  void fly() {
    printf("I can't fly!\n");
  }
};


class QuackBehavior {

public:
  virtual void quack();
};


class Quack : QuackBehavior {

public:
  void quack() {
    printf("Quack!\n");
  }
};


class MuteQuack : QuackBehavior {

public:
  void quack() {
    printf("<< Silence >>\n");
  }
};


class Squeak : QuackBehavior {

public:
  void quack() {
    printf("Squeak!\n");
  }
};


class Duck {

public:
  virtual void display();

  void performFly() {
    flyBehavior->fly();
  }

  void performQuack() {
    quackBehavior->quack();
  }

  void swim() {
    printf("All ducks float, even decoys!\n");
  }

protected:
  FlyBehavior* flyBehavior;
  QuackBehavior* quackBehavior;
};


class MallardDuck : Duck {

public:
  MallardDuck() {
    quackBehavior = new Quack();
    flyBehavior = new FlyWithWings();
  }

  ~MallardDuck() {
    delete quackBehavior;
    delete flyBehavior;
  }

  void display() {
    printf("I'm a real Mallard duck.\n");
  }
};
int main() {
  Duck* mallard = new MallardDuck();
  mallard->performQuack();
  mallard->performFly();
  return 0;
}
