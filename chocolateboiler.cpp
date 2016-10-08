/**
 * Chocolate Boiler
 * Singleton pattern example
 */

class ChocolateBoiler {
public:
  ChocolateBoiler(const ChocolateBoiler& boiler) = delete;
  ChocolateBoiler& operator=(const ChocolateBoiler& boiler) = delete;

  static ChocolateBoiler& getInstance() {
    return uniqueInstance;
  }
  
  void fill() {
    if(isEmpty()) {
      empty = false;
      boiled = false;
    }
  }

  void drain() {
    if(!isEmpty() && isBoiled())
      empty = true;
  }

  void boil() {
    if(!isEmpty() && !isBoiled())
      boiled = true;
  }

  bool isEmpty() {
    return empty;
  }

  bool isBoiled() {
    return boiled;
  }

private:
  ChocolateBoiler() : empty { true }, boiled { false } {};
  
  static ChocolateBoiler uniqueInstance;
  bool empty;
  bool boiled;
};

ChocolateBoiler ChocolateBoiler::uniqueInstance;

int main() {
  auto& chocolateBoiler = ChocolateBoiler::getInstance();
  chocolateBoiler.fill();
  chocolateBoiler.boil();
  chocolateBoiler.drain();
  return 0;
}
