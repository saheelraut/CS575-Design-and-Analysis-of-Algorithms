#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstring>

using namespace std;
// creating stuct for vector
struct card
{
  string playerName;
  int marketPrice;
  int listPrice;
};

struct input
{
  int number;
  int budgetforpurchase;
  vector<card> cards;
};

struct outcome
{
  int profitoutcome;
  int inputcards;
  int numcardspurchased;
  double time;
  int maxprofit;
  vector<card> cards1;
  string attribute1;
  int attribute2;
};

vector<card> finalvector;

outcome computeMaxProfit(input a)
{
 
  int start_s = clock(); // Clock for checking execution time

  int maxProfit = 0;
  int totalprice = 0;
  int highestprofit = 0;
  int currentprofit = 0;
  int cardnumber;
  vector<vector<card> > powerset;
  vector<card> subsetvector1;

  int budget = a.budgetforpurchase;
  for (int i = 0; i < a.cards.size(); i++)
  {
    totalprice += a.cards[i].listPrice;
  }

  if (totalprice < budget || totalprice == budget)
  {
    for (int i = 0; i < a.cards.size(); i++)
    {

      subsetvector1.push_back(a.cards[i]);
      maxProfit += a.cards[i].marketPrice - a.cards[i].listPrice;
      currentprofit = a.cards[i].marketPrice - a.cards[i].listPrice;
      if (currentprofit >= highestprofit)
      {
        highestprofit = currentprofit;
        cardnumber = i;
      }
    }
    powerset.push_back(subsetvector1);
    finalvector = subsetvector1;
  }
  else
  {
    for (int i = 0; i < pow(2, a.cards.size()); i++)
    {
      vector<card> subsetvector2;
      for (int j = 0; j < a.cards.size(); j++)
      {
        if (i & (1 << j))
        {
          subsetvector2.push_back(a.cards[j]);
        }
      }
      powerset.push_back(subsetvector2);
    }
    int currProfit = 0;
    int currprice = 0;
    for (int i = 0; i < powerset.size(); i++)
    {
      vector<card> curr = powerset[i];
      for (int j = 0; j < powerset[i].size(); j++)
      {
        currProfit += curr[j].marketPrice - curr[j].listPrice;
        currentprofit = a.cards[j].marketPrice - a.cards[j].listPrice;
        if (currentprofit >= highestprofit)
        {
          highestprofit = currentprofit;
          cardnumber = j;
        }
        currprice += curr[j].listPrice;
      }
      if (currprice < budget || currprice == budget)
      {
        if (currProfit > maxProfit)
        {
          maxProfit = currProfit;
          finalvector = curr;
        }
      }
      currProfit = 0;
      currprice = 0;
    }
  }
  outcome o;
  o.numcardspurchased = finalvector.size();
  o.profitoutcome = maxProfit;
  o.inputcards = a.cards.size();
  o.maxprofit = highestprofit;
  o.attribute1 = a.cards[cardnumber].playerName;
  o.attribute2 = a.cards[cardnumber].listPrice;

  //int max = *max_element(profit.begin(), profit.end());
  //o.highestprofit = max;

  //end = std::chrono::high_resolution_clock::now();
  //std::chrono::duration<double> duration = duration_cast<seconds>(end - start);
  //o.time = duration.count();

  int stop_s = clock();
  o.time = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
  //o.time *= 1e-9;
  return o;
};

int main(int argc, char *argv[])
{
  int numcards = 0;
  int cardnumber;
  if (argc != 5)
  {
    cout << "Wrong Input Count";
    exit(1);
  }
  else if ((strcmp(argv[1], "-m") != 0) || (strcmp(argv[3], "-p") != 0))
  {
    cout << "Wrong input Parameters";
    exit(1);
  }

  ifstream marketFile(argv[2]);
  ifstream priceFile(argv[4]);

  if (!(marketFile.is_open() && priceFile.is_open()))
  {
    cout << "Files not found.\n";
    exit(1);
  }
  vector<card> gurtiescards;
  vector<input> inputvector;
  vector<outcome> outputvector;

  while (marketFile >> numcards)
  {
    int i = 0;
    while (i < numcards)
    {
      i++;
      card c;
      string cardname;
      int mktprice;
      marketFile >> cardname;
      marketFile >> mktprice;
      c.playerName = cardname;
      c.marketPrice = mktprice;
      gurtiescards.push_back(c);
    }
  }
  marketFile.clear();
  marketFile.close();

  int saleslist;
  int inputbudget;
  string playercardname;
  int playerprice;
  while (priceFile >> saleslist >> inputbudget)
  {
    input a;
    int i = 0;
    a.number = saleslist;
    a.budgetforpurchase = inputbudget;
    while (i < saleslist)
    {
      i++;
      priceFile >> playercardname;
      priceFile >> playerprice;
      for (int j = 0; j < gurtiescards.size(); j++)
      {
        if (playercardname.compare(gurtiescards[j].playerName) == 0)
        {
          gurtiescards[j].listPrice = playerprice;
          a.cards.push_back(gurtiescards[j]);
        }
      }
    }
    inputvector.push_back(a);
  }
  priceFile.clear();
  priceFile.close();
  ofstream output;
  output.open("output.txt");
  for (int i = 0; i < inputvector.size(); i++)
  {
    outcome o = computeMaxProfit(inputvector[i]);
    output << o.inputcards << "  " << o.profitoutcome << "  " << o.numcardspurchased << "  " << o.time << " Seconds" << endl;
    //output<<o.attribute1<<" "<< o.attribute2<< endl;
    for (int j = 0; j < finalvector.size(); j++)
    {
      output << finalvector[j].playerName << " " << finalvector[j].listPrice << endl;
    }
  }
  output.close();
}