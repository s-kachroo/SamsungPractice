#include<iostream>
using namespace std;
struct node{   
    int x, y;
};

int abs(int x){
    return (x<0) ? -x : x;
}

int finddist(struct node *first,struct node *second){
	int dstx = abs(first->x - second->x);
	int dsty = abs(first->y - second->y);
	return dstx + dsty;
}

int main(){
    int test;
    cin >> test;
    for(int t=1;t<=test;t++){
        int warmholes;    
        cin>>warmholes;

        /* Initialise Code */
	    int nodes = 2 * warmholes + 2;
	  	struct node *location[nodes];
	  	
        int cost[nodes][nodes];
	  	for(int i=0;i<nodes;i++){
	  		for(int j=0;j<nodes;j++){
	  			cost[i][j]=-1;
			}
		}

		//source
		  int sx, sy;
		  cin>>sx>>sy;
		  struct node *src=new struct node;
		  src->x=sx;
		  src->y=sy;
		  location[0]=src;

		//destination
		  int dox,doy;
		  cin>>dox>>doy;
		  struct node *temp=new node;
		  temp->x=dox;
		  temp->y=doy;
		  location[nodes-1]=temp;

        //warmhole
		  for(int i=0;i<warmholes;i++){
		  	int six, siy;
		  	cin>>six>>siy;
		  	struct node *temp=new node;
			  	temp->x=six;
			  	temp->y=siy;
				
            int dix,diy;
		  	cin>>dix>>diy;
		  	struct node *temp1=new node;
			  	temp1->x=dix;
			  	temp1->y=diy;
			
			int w;
		  	cin>>w;
		  	
            location[2*i+1]=temp;
		  	location[2*i+2]=temp1;
		  	cost[2*i+1][2*i+2]=w;
		  	cost[2*i+2][2*i+1]=w;
          }

        // Initialise cost matrix      
            for(int i=0;i<nodes;i++){
                for(int j=0;j<nodes;j++){
		  		    if(cost[i][j] == -1){
		  			cost[i][j] = finddist(location[i],location[j]);
				    }
			    }
    		}

       // Floyd Warshall
            for(int k=0;k<nodes;k++){
                for(int i=0;i<nodes;i++){
                    for(int j=0;j<nodes;j++){
                        if(i==k||j==k)
                            continue;
                        cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
                    }
                }
            }

        cout << "#" << t << " : " << cost[0][nodes-1] << "\n";
    }
    return 0;
}
