#include <iostream> 
#include <bits/stdc++.h>
 
// uri 2406
// uri 1030
using namespace std;

int main() 
{ 
	int num, discarded1, discarded2, i;
 
	while(scanf("%d", &num) && num != 0)
	{
		queue<int> deck;
		for (i = 1; i <= num; i++)
			deck.push(i);

		i = 0;
		printf("Discarded cards:");
		while(deck.size() > 1)
		{
			discarded1 = deck.front();
			deck.pop();
			discarded2 = deck.front();
			deck.pop();
			deck.push(discarded2);
			if (i > 0)
				printf(",");
			
			printf(" %d",discarded1);
			i++;
		}
		printf("\nRemaining card: %d\n", deck.front());
	}
 
	return 0; 
}