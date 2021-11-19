#include <bits/stdc++.h>
#include<cmath>
using namespace std;
#define DIM 2

int check_match(int** prev_clusters, int** new_clusters, int k, int num_points)
{
	int i,j;
	int flag = 1, flag1;
	cout << "\nNew Clusters are\n";
	for( i=0 ; i<k ; i++ )
	{
		for( j=0 ; j<num_points ; j++ )
		{
			if( new_clusters[i][j] != -1 )
				cout << new_clusters[i][j] << " ";
		}
		cout << endl;
	}
	for( i=0 ; i<k && flag == 1 ; i++ )
	{
		flag1 = 1;
		for( j=0 ; j<num_points && flag1 == 1 ; j++ )
		{
			if( prev_clusters[i][j] != new_clusters[i][j] )
			{
				flag1 = 0;
				return 0;
			} 
		}
		if( flag1 == 0 )
		{
			flag = 0;
			return 0;
		}
	}
	
	return 1;
}

vector< vector<float> > update_centroids(float** points, vector< vector<float> >& centroids, int** new_clusters, int k, int num_points)
{
	int i,j,p;
	float sum,avg;
	int pt;
	int flag = 1;
	int count;
	
	for( i=0 ; i<k ; i++ )
	{
		for( p=0 ; p<DIM ; p++ )
		{
			sum = 0.0;
			flag = 1;
			count = 0;
			for( j=0 ; j<num_points && flag == 1 ; j++ )
			{
				if( new_clusters[i][j] != -1 )
				{
					pt = new_clusters[i][j];
					sum = sum + points[pt][p];
					count++;
				}
				else
				{
					flag = 0;
				}	
			}
			avg = sum/count;
			centroids[i][p] = avg;
		}
	}
	return centroids;
}

int** k_means_clustering(float** points, vector< vector<float> >& centroids, int k, int num_points, int** clusters )
{
	
	float* distance = new float[k];
	int i,j,p;
	float diff;
	float sum;
	float dist;
	float min;
	int min_clus,flag;
	
	for( i=0 ; i<num_points ; i++ )
	{
		for( p=0 ; p<k ; p++ )
		{
			sum = 0;
			for( j=0 ; j<DIM ; j++ )
			{
				diff = centroids[p][j] - points[i][j];
				diff = diff * diff;
				sum = sum + diff;
			}
			dist = sqrt(sum);
			//cout << "sum " << sum << " % ";
			distance[p] = dist;
		}
		//cout << endl;
		min = INT_MAX;
		for( p=0 ; p<k ; p++ )
		{
			if( distance[p] < min )
			{
				min = distance[p];
				min_clus = p;
			}
		}
		
		flag = 1;
		for( p=0 ; p<num_points && flag == 1 ; p++ )
		{
			if( clusters[min_clus][p] == -1 )
			{
				clusters[min_clus][p] = i;   //store the point number
				flag = 0;
			}
		}
		
	}
	
	cout << "\nClusters are\n";
	for( i=0 ; i<k ; i++ )
	{
		for( j=0 ; j<num_points ; j++ )
		{
			if( clusters[i][j] != -1 )
				cout << clusters[i][j] << " ";
		}
		cout << endl;
	} 
	
	return clusters;
}

int main()
{
	int k,num_points;
	cout << "Enter the value of k\n";
	cin >> k;
	cout << "Enter number of 5D points\n";
	cin >> num_points;
	int i,j;
	
	cout << "Enter 5D points\n";
	float** points = new float*[num_points];
    	for (i = 0; i < num_points; i++)
    	{   
        	points[i] = new float[DIM];
    	}
	
	for( i=0 ; i<num_points ; i++ )
	{
		for( j=0 ; j<DIM ; j++ )
		{
			cin >> points[i][j];
		}
	}
	cout << "\nPoints are \n";
	for( i=0 ; i<num_points ; i++ )
	{
		cout << "Point(" << i << ") : ";
		for( j=0 ; j<DIM ; j++ )
		{
			cout << points[i][j] << " ";
		}
		cout << endl;
	}
	
	vector< vector<float> > centroids;
	int** clusters = new int*[k];
    	for (i = 0; i < k; i++)
    	{   
        	clusters[i] = new int[num_points];
    	}
    	/*int** new_clusters = new int*[k];
    	for (i = 0; i < k; i++)
    	{   
        	new_clusters[i] = new int[num_points];
    	}*/
    	int** prev_clusters = new int*[k];
    	for (i = 0; i < k; i++)
    	{   
        	prev_clusters[i] = new int[num_points];
    	}
	
	for( i=0 ; i<k ; i++ )
	{
		for( j=0 ; j<num_points ; j++ )
		{
			prev_clusters[i][j] = -5;
			clusters[i][j] = -1;
		}
	}
	
	int jump = 0;
    	for( i=0 ; i<k ; i++ )
	{
		vector< float > temp;
		for( j=0 ; j<DIM ; j++ )
		{
			temp.push_back(points[jump][j]);
		}
		centroids.push_back(temp);
		jump = jump + k;
	}
	
	cout << "\nInitial Centroids are \n";
	for( i=0 ; i<centroids.size() ; i++ )
	{
		for( j=0 ; j<centroids[i].size() ; j++ )
		{
			if( centroids[i][j] != -1 )
				cout << centroids[i][j] << " ";
		}
		cout << endl;
	}
	
	int flag = 1;
	int match;
	int flag1,flag2;
	
	while( flag == 1 )
	{
		clusters = k_means_clustering(points,centroids,k,num_points,clusters);
		
		match = check_match(prev_clusters,clusters,k,num_points);
		
		if( match == 1 )
		{
			
			flag = 0;
			cout << " Stop!!! " << endl;
		} 
		else
		{
			centroids = update_centroids(points,centroids,clusters,k,num_points);
			cout << "\nNew Centroids are \n";
			for( i=0 ; i<centroids.size() ; i++ )
			{
				for( j=0 ; j<centroids[i].size() ; j++ )
				{
					if( centroids[i][j] != -1 )
						cout << centroids[i][j] << " ";
				}
				cout << endl;
			}
			
			for( i=0 ; i<k ; i++ )
			{
				for( j=0 ; j<num_points ; j++ )
				{
					prev_clusters[i][j] = clusters[i][j];
				}
			
			}
			
			for( i=0 ; i<k ; i++ )
			{
				for( j=0 ; j<num_points ; j++ )
				{
					clusters[i][j] = -1;
				}
			}
			
		}
		
	}
	return 0;
}

/*INPUT
7 9 3 4 1
-3 4 -6 9 -8 
6 12 -3 7 1
0 4 -7 3 -5
-9 3 6 1 4
-13 7 2 -5 3
11 5 -14 0 3
3 -6 18 5 -8


2 10
2 5
8 4
5 8
7 5
6 4
1 2
4 9
*/
