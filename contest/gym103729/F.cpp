#include <cstdio>
#include <vector>

int n;
std::vector<int> ans;

void out(){
    printf("%d\n", (int)ans.size());
    for(int i : ans) printf("%d ", i);
}

int main(){
    scanf("%d", &n);
    if(n == 1){
        printf("1\n1\n");
        return 0;
    }else if(n == 2 || n == 3){
        printf("2\n2 2\n");
        return 0;
    }else if(n == 4){
        ans.push_back(2);
        ans.push_back(3);
        ans.push_back(3);
        ans.push_back(2);
        out();
    }else if(n == 5){
        ans.push_back(2);
        ans.push_back(3);
        ans.push_back(4);
        ans.push_back(2);
        ans.push_back(3);
        ans.push_back(4);
        out();
    }else{
        puts("-1");
    }
}