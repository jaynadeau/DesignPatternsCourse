
//
// Command Coding Exercise
//
//     Implement the Account::Process() function to process different commands. The rules are obvious:
//
//         - success indicates whether the operation was successful.
//         - You can only withdraw money if you have enough in your account.
//

#include <iostream>
#include <list>
using namespace std;

struct Command
{
  enum Action { deposit, withdraw } action;
  int amount{0};
  bool success{false};
};

struct Account
{
  int balance{0};

  void process(Command& cmd)
  {
    switch(cmd.action)
    {
    case Command::Action::deposit:
        cout << "Account processing deposit of: " << cmd.amount << " with opening balance: " << balance << endl;
        balance += cmd.amount;
        cmd.success = true;
        cout << "New balance: " << balance << endl;
        break;
    case Command::Action::withdraw:
        cout << "Account processing withdraw of: " << cmd.amount << " with opening balance: " << balance << endl;
        if(cmd.amount <= balance)
        {
            balance -= cmd.amount;
            cmd.success = true;
        }
        else
        {
            cmd.success = false;
        }
        cout << "New balance: " << balance << endl;
        break;
    default:
        // do nothing
        break;
    }
  }
};

struct Transaction
{
    void commit(Account& acct, list<Command>& commands)
    {
        cout << "Committing transaction..." << endl;
        for(auto& command : commands)
        {
            acct.process(command);
        }
        cout << "Commit complete..." << endl;
    }

    bool execute(Account acct, list<Command> commands)
    {
        cout << "Attempting transaction..." << endl;
        bool success = false;
        for(auto command : commands)
        {
            acct.process(command);
            if(!(success = command.success))
            {
                cout << "Transaction failed!" << endl;
                break;
            }
        }
        return success;
    }

    void process(Account& account, list<Command>& commands)
    {
        cout << "Processing transaction..." << endl;
        bool success = execute(account, commands);
        cout << "Interim account balance: " << account.balance << endl;
        if(success)
        {
            commit(account, commands);
        }
        cout << "Final account balance: " << account.balance << endl;
    }
};

int main(int argc, char* argv[])
{
    Account account;
    account.balance = 100;
    Transaction transaction;
    list<Command> commands{{Command::Action::deposit, 50, false}, {Command::Action::withdraw, 20, false}};
    transaction.process(account, commands);
    Account account2;
    account2.balance = 50;
    commands.emplace_back(Command{Command::Action::withdraw, 200, false});
    transaction.process(account2, commands);

    return 0;
}

