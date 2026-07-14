#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  std::vector<int> nums = {11, 15, 7, 7};
  int target = 9;
  std::unordered_map<int,int> numMap;
  int n = nums.size();
  for (int i = 0; i < n; i++){
    numMap[nums[i]] = i;
  }
  std::sort(nums.begin(), nums.end());
  auto lambda = [target](int element) { return (element > target); };
  auto end = std::find_if(nums.begin(), nums.end(), lambda) - 1;
  auto it = nums.begin();
  for (; it != end; it++) {
    if (*it+*end>target)
      end--;
    else{
      if (*it+*end<target)
        it++;
      else {
        std::cout << int(it-nums.begin()) << " " << int(end-nums.begin());
        break;
      }
    }
  }

  return 0;
}
