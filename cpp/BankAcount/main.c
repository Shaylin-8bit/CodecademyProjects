#include <iostream>
#include <map>
#include <vector>

std::map<std::string, float> gen_map(void) {
  std::map<std::string, float> result;
  result.insert(std::pair<std::string, float>("dollar", 1.0));
  result.insert(std::pair<std::string, float>("sole", 1.3));
  result.insert(std::pair<std::string, float>("peso", 1.7));
  result.insert(std::pair<std::string, float>("reai", 0.9));

  return result;
}


class Account {
  std::string _name;
  float _balance;

  public:
  Account (std::string name, float balance) {
    _name = name;
    _balance = balance;
  }

  void deposit(float amount) {
    _balance += amount;
  }

  float withdraw(float amount) {
    if (_balance >= amount) {
      _balance -= amount;
      return amount;
    } else {
      std::cout << "Withdraw exceeds ballance\n";
      return 0;
    }
  }

  float get_balance() {
    return _balance;
  }

  std::string get_name() {
    return _name;
  }
};


class Bank {
  float _amount;
  std::string _name;
  std::map<std::string, float> _map;
  std::vector<Account> _accounts;

  public:

int get_acc(std::string name) {
    for (int i = 0; i < _accounts.size(); i++) {
      if (_accounts[i].get_name() == name) {
        return i;
      }
    }
    return -1;
  }

  Bank(std::string name, float amount) {
    _map = gen_map();
    _name = name;
    _amount = amount;
    std::cout << name + " created!\n";
  }

  void new_account(std::string name, float balance) {
    if (name != "NULL" && get_acc(name) == -1 && balance >= 0) {
      _accounts.push_back(Account(name, balance));
      _amount += balance;
    } else {
      std::cout << "Negative balance entered, could not create account\n";
    }
  }

  void deposit(std::string name, float amount) {
    int i = get_acc(name);
    if (i != -1) {
      if (amount > 0) {
        _accounts[i].deposit(amount);
        std::cout << std::to_string(amount) + " deposited\n";
      } else {
        std::cout << "Can't deposit no or negative money\n";
      }
    } else {
      std::cout << "No account {" + name + "}\n";
    }
  }


  float withdraw(std::string name, float amount, std::string type="dollar") {

    float m = _map[type];

    int i = get_acc(name);
    if (i != -1) {
      std::cout << "Withdrawing " + std::to_string(amount) + "\n";
      float a = _accounts[i].withdraw(amount)*m;
      if (a) {
        _amount -= amount*m;
        return a;
      } else {
        return 0;
      }
      
    } else {
      std::cout << "No account {" + name + "}\n";
      return 0;
    }
  }

  float balance(std::string name) {
    int i = get_acc(name);
    if (i != -1) {
      return _accounts[i].get_balance();
    } else {
      std::cout << "No account {" + name + "}\n";
      return 0;
    }
  }
};


int main(void) {
  
  Bank my_bank = Bank("Billy Bob's Bankin' Bank", 500);
  
  my_bank.new_account("Tom", -300);
  my_bank.deposit("Tom", -300);
  my_bank.withdraw("Tom", 300, "peso");
  
  return 0;
}
