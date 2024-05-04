#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Logic : As the Longest mountain subarray is also a part of the array...and its peak also lies in the array...so we consider each element as peak...and find the length of he mountain subarray...
    int bruteForce(vector<int> &arr)
    {
        int n = arr.size();
        int maxi = INT_MIN;

        // considering this as peak...
        for (int i = 0; i < n; i++)
        {

            // checking left of this peak element...how many contigous decreasing element from this point
            int left = 0;
            for (int j = i - 1; j >= 0; j--)
            {
                if (arr[j] < arr[j + 1])
                {
                    left++;
                }
                else
                {
                    break;
                }
            }

            // checking right of this peak element...how many contigous decreasing element from this point
            int right = 0;
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[j - 1])
                {
                    right++;
                }
                else
                {
                    break;
                }
            }

            maxi = max(maxi, left + right + 1); // adding 1 for the peak element
        }

        return maxi;
    }

    // Logic : In bruteForce...we are considering each element as peak...whch is correct...but we are travelling in same direction again and again...which is not good...here why...suppose the array we have is something like .... {.,.,.,.,.,.,.,100,101}..now when we were at 100...we calculated the contigous subarray to its left...in decreasing order ....now when we are at element 101...we dont need to check again....let's say before 100...the lenght of the contigous decreasing subarray is 3...now when we are 101..we know 100<101..so for 101...the length of the contigous decreasing left subarray will ofcourse 3+1=4...so we use the same logic :)
    int better(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> leftIncreasing(n, 1), rightIncreasing(n, 1);

        // making the leftIncreasing Array...such that leftIncreasing[i] gives the length of the longest increasing subarray till this index(including)..from left
        for (int i = 1; i < n; i++)
        {
            if (arr[i] > arr[i - 1])
            {
                leftIncreasing[i] = leftIncreasing[i - 1] + 1;
            }
            else
            {
                continue;
            }
        }

        // Similarly making rightIncreasing...as when we see from both the foot of the mountain...we will be increasing thevalue towards the peak....
        for (int i = n - 2; i >= 0; i--)
        {
            if (arr[i] > arr[i + 1])
            {
                rightIncreasing[i] = rightIncreasing[i + 1] + 1;
            }
            else
            {
                continue;
            }
        }

        // now as we have leftIncreasing and rightIncreasing....we will consider each element as peak...and then find the max Mountain subarray..
        int maxi = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            maxi = max(maxi, leftIncreasing[i] + rightIncreasing[i] - 1); // here -1...because we have included peak in the leftIncreasing and rightIncreasing both...so we need to remove its one instance...
        }

        return maxi;
    }

    // Logic : If we observe carefully...we always have contigous mountains in our array...and what we need to find is the one mountain..which has the highest length...we know ...a mountain is something..in which our state changes fro increasing ..till peak...then state changes to decreasing....so thi is a mountain...but what if my state changes from decreasing -> increasing...this simply signifies....that we have traversed a mountain earlier....so just take any testCase ...and when u dry run...u will see it..and once ur state changes from decreasing to increasin => u just traversed a mountain....so we think of a 2-pointer approach...
    int optimal(vector<int> &arr)
    {

        int n = arr.size();

        // this variable tell which state we should be...
        bool stateIncreasing = (arr[1] > arr[0]) ? true : false; // true => increasing State..... false => decreasing State

        int i = 0, j = 1; // i => start of mountain....`j` is used to traverse the array...

        int maxi = INT_MIN;
        while (j < n)
        {
            if (stateIncreasing)
            {
                if (arr[j] > arr[j - 1])
                {
                    j++; // in favour
                }
                else
                {
                    stateIncreasing = false; // we are supposed to be increasing...but as we got a smaller value...we are now in decreasing state...
                }
            }
            else
            {
                if (arr[j] < arr[j - 1])
                {
                    j++; // favourable
                }
                else
                {
                    // we were supposed to be decreasing state...but got a large value...which means state changing from
                    // Decreasing => Increasing..which means....we got a mountain...
                    maxi = max(maxi, j - i);
                    i = j - 1; // moving `i` to the start of the last mountain....
                    stateIncreasing = true;
                }
            }
        }

        // at the end..we might have the case..when our mountain is just increasing or decreasing...so we wouldn't have included that part in our maxi...so
        maxi = max(maxi, j - i);

        return maxi;
    }
};

int main()
{

    Solution obj;
    vector<int> arr = {1, 3, 1, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5};

    cout << obj.bruteForce(arr) << endl; // TC - O(n^2) .... SC - O(1)
    cout << obj.better(arr) << endl;     // TC - O(3n) .... SC - O(2n)
    cout << obj.optimal(arr) << endl;    // TC - O(n) .... SC - O(1)
    return 0;
}