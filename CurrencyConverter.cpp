#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <time.h>

int main ()
{
    int price;
    double rates;
    int m;
    int k;
    int d;
    std:: string item;
    std:: string line;
    std:: string paraline;
    std:: fstream purchase;
    std:: fstream param;
    std:: queue<double>animeRates;
    std:: queue <int> animePrice;
    clock_t start = clock();

    purchase.open("m_purchases.txt");

    while (std::getline(purchase, line))
    {
        std:: stringstream name(line);
        while (name.eof() == false)
        {
            name >> item;
            if (std:: stringstream(item)>>price)
            {};
        }
        animePrice.push(price);
    }
    purchase.close();
    
    param.open("m_params.txt");
    param >> d;
    param >> k;
    param >> m;
    while (true)
    {
        if (std:: getline(param, paraline))
        {
            param >> rates;
            animeRates.push(rates);
        }
        else
        {
            break;
        }
    }
    param.close();
 
    int dcount = 2;
    int pcount = 2;
    double min = animeRates.front();
    int i = 0;
    animeRates.pop();
    double total = 0;
    double items = 0;

    //std:: cout << "p " << "d " << "rate: " << "price: " << "purchase: " << '\n';
    while(dcount != d)
    {
        if(pcount < k && pcount < m && min < animeRates.front())
        {
            //std:: cout << pcount << ' ' << dcount << ' '  << "rate: " << animeRates.front() << " cond 1.1" << '\n';
            animeRates.pop();
            dcount++;
            pcount++;
        }

        else if (pcount < k && pcount < m && min >= animeRates.front())
        {
            //std:: cout << pcount << ' ' << dcount << ' '  << "rate: " << animeRates.front() << " cond 1.2" << '\n';
            min=animeRates.front();
            animeRates.pop();
            pcount++;
            dcount++;
        }

        else if (pcount == k && pcount < m && min >= animeRates.front())
        {
            min = animeRates.front();
            items = min * animePrice.front();
            total += items;
            //std:: cout << pcount << ' ' << dcount << ' '  << "rate: " << min << ' ' << "price: " << animePrice.front() << ' ' << "items: " << items <<  " cond 2.1" << '\n';
            animePrice.pop();
            animeRates.pop();
            min = animeRates.front();
            pcount = 1;
            dcount++;
        }

        else if (pcount == k && pcount < m && min < animeRates.front())
        {
            //std:: cout << pcount << ' ' << dcount << ' '  << "rate: " << animeRates.front() << " cond 2.2" << '\n';
            animeRates.pop();
            pcount++;
            dcount++;
        }

        else if (pcount > k && pcount < m && min > animeRates.front())
        {
            min = animeRates.front();
            items = min * animePrice.front();
            total += items;
            //std:: cout << pcount << ' ' << dcount << ' '  << "rate: " << min << ' ' << "price: " << animePrice.front() << ' ' << "items: " << items << " cond 3.1" << '\n';
            animePrice.pop();
            animeRates.pop();
            min = animeRates.front();
            pcount = 1;
            dcount++;
        }
        else if (pcount > k && pcount < m && min <= animeRates.front())
        {   
            //std:: cout << pcount << ' ' << dcount << ' '  << "rate: " << animeRates.front() << " cond 3.2" << '\n';
            animeRates.pop();
            pcount++;
            dcount++;
        }
        else if (pcount == m && pcount > k)
        {
            min = animeRates.front();
            items = min * animePrice.front();
            total += items;
            //std:: cout << pcount << ' ' << dcount << ' '  << "rate: " << min << ' ' << "price: " << animePrice.front() << ' ' << "items: " << items << " cond 4.1" << '\n';
            animePrice.pop();
            animeRates.pop();
            min = animeRates.front();
            pcount = 1;
            dcount++;
        }
    i++;
    }

    if (d == dcount)
    {
        min = animeRates.front();
        animeRates.pop();
        while(animePrice.empty() == false)
        {
            items = min*animePrice.front();
            total += items;
            //std:: cout << pcount << ' ' << dcount << ' '  << "rate: " << min << ' ' << "price: " << animePrice.front() << ' ' << "items: " << items << " cond 5.1" << '\n';
            animePrice.pop();
        }
    }
    std:: cout << "Total: " << total << '\n';
    std:: cout << "# of loop: " << i << '\n';
    printf("%.3fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
    return 0;
}