#include <iostream> 
#include <bits/stdc++.h>
 
using namespace std;
 
// determine o maior valor total que possa ser obtido com
// o corte de um cano de comprimento inicial determinado

int main() 
{ 
	int num_pipes, pipe_length;
	int pipe_lenghts[1010] = {0}, values[1010] = {0};
	scanf("%d", &num_pipes, pipe_length);
	for (int i = 0; i < num_pipes; i++)
	{
		scanf("%d %d", &pipe_lenghts[i], &values[i]);
	}
	
 
	printf("%d", num_pipes, pipe_length);
 
	return 0; 
}
