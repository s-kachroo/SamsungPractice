#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;

#define scll(x) scanf("%lld",&x);
#define sci(x) scanf("%d",&x);
#define prll(x) printf("%lld\n",x);
#define pri(x) printf("%d\n",x);

/*
3 
(0(5(6()())(-4()(9()())))(7(1()())(3()())))
*/

int main()
{
	int arr[2][100]={0};	
	int size = 0;
	int x;
	string str;
	
	cin>>x;
	cin>>str;
	int level=0, temp=0, commit=0, neg=0;
	for(int i=0; i<str.length(); i++){
		
		if(str[i]=='(' || str[i]==')'){
			if(commit == 1){
				if(neg==1){
					temp=temp*-1;
					neg=0;
				}
				
				arr[0][size]=level;
				arr[1][size]=temp;
				size++;
				temp=0;		
			}
			
			if(str[i]=='('){			
				level++;
			}
			else if(str[i]==')'){
				level--;
			}
			commit=0;
		}
		else if(str[i]=='-'){
			neg=1;
			commit = 1;
		}
		else{
			temp= temp*10 + str[i] - '0';
			commit = 1;
		}	
			
	}

	int temp0,temp1;
	for(int i=0;i<size-1;i++){
		for(int j=i+1; j<size; j++){
			if(arr[0][j] > arr[0][i]){
				temp0=arr[0][j];
				temp1=arr[1][j];
				arr[0][j]=arr[0][i];
				arr[1][j]=arr[1][i];
				arr[0][i]=temp0;
				arr[1][i]=temp1;
			}
			
		}
	}
	
	int sum = 0;
	for(int i=0;i<size;i++){
		if(arr[0][i]==x+1)	sum+=arr[1][i];
	}
	
	cout<<sum<<endl;
	return 0;
}
